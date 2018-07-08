#include "world/Database.h"

GibEngine::World::Database::Database(const std::string& databaseFilepath, std::shared_ptr<FileSystem::IFileSystem> fs, std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi) : Database(databaseFilepath, fs, graphicsApi, false) { }

GibEngine::World::Database::Database(const std::string& databaseFilepath, std::shared_ptr<FileSystem::IFileSystem> fs, std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, bool debugMode)
	: fs(fs), graphicsApi(graphicsApi), debugMode(debugMode)
{
    std::ifstream dbFile(databaseFilepath);
    bool dbExists = dbFile.good();

	db = std::shared_ptr<sqlite3pp::database>(new sqlite3pp::database(databaseFilepath.c_str()));

    if(!dbExists)
    {
        int res = db->execute(DatabaseQuery::CREATE_DATABASE_COMMAND.c_str());
    
        if(res != SQLITE_OK)
        {
			const std::string errorMessage = db->error_msg();
            Logger::Instance->error("Failed to create WorldDb: {}", errorMessage);
        }
    }
}

GibEngine::World::Database::~Database()
{
	Disconnect();
}

void GibEngine::World::Database::Disconnect()
{
	db->disconnect();
}

bool GibEngine::World::Database::CreateLevel(int rootNodeId, const std::string& name)
{
    sqlite3pp::command insertCmd(*db, DatabaseQuery::CREATE_LEVEL_COMMAND.c_str());
	insertCmd.bind(":nodeId", rootNodeId);
	insertCmd.bind(":name", name, sqlite3pp::nocopy);
    int res = insertCmd.execute();

    if(res != SQLITE_OK)
    {
		const std::string errorMessage = db->error_msg();
        Logger::Instance->error("Failed to create WorldDb Level! SQLite Error: {}", errorMessage);
		return false;
    } 

	return true;
}

GibEngine::Skybox* GibEngine::World::Database::LoadSkybox(int skyboxId)
{
	sqlite3pp::query qry(*db, DatabaseQuery::SELECT_SKYBOX_QUERY.c_str());
	qry.bind(":id", skyboxId);

	const char* assetName;
	const char* extension;

	auto queryIter = qry.begin();
	std::tie(assetName, extension) = (*queryIter).get_columns<const char*, const char*>(0, 1);

	// TODO: Change to shared_ptr once refactor is mostly done:
	auto cubeMesh = MeshService::Generate(graphicsApi, MeshService::CUBE_GENERATION_JSON);
	auto cubeMap = MeshService::LoadCubemap(graphicsApi, fs->GetWorkingDirectory() + "/../../Assets/Skybox/" + assetName, extension);

	return new Skybox(cubeMesh, cubeMap);
}

GibEngine::PointLight* GibEngine::World::Database::LoadLight(int lightId)
{
	sqlite3pp::query qry(*db, DatabaseQuery::SELECT_LIGHT_QUERY.c_str());
	qry.bind(":id", lightId);

	for (auto iter = qry.begin(); iter != qry.end(); ++iter)
	{
		const char* lightType;
		const char* ambient;
		const char* diffuse;
		const char* specular;
		float linearAtten;
		float quadAtten;

		std::tie(lightType, ambient, diffuse, specular, linearAtten, quadAtten) =
			(*iter).get_columns<const char*, const char*, const char*, const char*, float, float>(0, 1, 2, 3, 4, 5);

		if (strcmp(lightType, "PointLight") == 0)
		{
			PointLight* pointLight = new PointLight(glm::vec3(),
				ReadVec3(ambient), ReadVec3(diffuse), ReadVec3(specular), linearAtten, quadAtten);

			return pointLight;
		}
	}

	return nullptr;
}

//std::shared_ptr<GibEngine::Mesh> GibEngine::World::Database::LoadMesh(int meshId)
//{
//	sqlite3pp::query qry(*db, DatabaseQuery::SELECT_MESH_QUERY.c_str());
//	qry.bind(":id", meshId);
//
//	for (auto iter = qry.begin(); iter != qry.end(); ++iter)
//	{
//		const std::string assetName = (*iter).get<const char*>(0);
//		const char* genData = (*iter).get<const char*>(1);
//
//		std::string parseError;
//		json11::Json generationDataJson = json11::Json::parse(genData, parseError);
//
//		if (!assetName.empty())
//		{ 
//			return MeshService::Load(graphicsApi, assetName, generationDataJson);
//		}
//		else if (generationDataJson != nullptr)
//		{
//			Scene::Node* node = new Scene::Node("Mesh Node");
//			node->SetNodeState(World::DatabaseRecord::State::NEW);
//			node->SetEntityState(World::DatabaseRecord::State::NEW);
//			// Attempt to use the generation data to build a Mesh internally:
//			node->SetEntity(MeshService::Generate(graphicsApi, generationDataJson));
//
//			return node;
//		}
//		else
//		{
//			Logger::Instance->info("Failed to LoadMesh: {}", parseError);
//			return nullptr;
//		}
//	}
//
//	return nullptr;
//}

//std::shared_ptr<GibEngine::BaseEntity> GibEngine::World::Database::LoadLevel(int id)
//{
//	return std::shared_ptr<BaseEntity>(new BaseEntity(BaseEntity::Type::ENTITY, "Level" + std::to_string(id)));
//	//return FindNode(rootNodeId);
//}

//bool GibEngine::World::Database::SaveLevel(Scene::Node* sceneRootNode)
//{
//	return SaveSceneNode(0, sceneRootNode);
//}

//bool GibEngine::World::Database::SaveMesh(Scene::Node* meshNode)
//{
//	// Return early if this is not a root mesh
//	if (!Scene::Node::FlagMask(meshNode->GetFlags() & Scene::Node::Flags::MESH_ROOT))
//	{
//		//return true;
//	}
//
//	Mesh* mesh = reinterpret_cast<Mesh*>(meshNode->GetEntity());
//
//	switch (meshNode->GetDatabaseRecord().GetEntityState())
//	{
//	case DatabaseRecord::State::CLEAN:
//		return true;
//	case DatabaseRecord::State::DIRTY:
//		return false;
//	case DatabaseRecord::State::NEW:
//		sqlite3pp::command insertCmd(*db, DatabaseQuery::CREATE_MESH_COMMAND.c_str());
//
//		auto meshAssetName = ""; // (mesh->GetOwnerAssetName() != nullptr) ? mesh->GetOwnerAssetName() : "";
//		insertCmd.bind(":assetName", meshAssetName, sqlite3pp::nocopy);
//		
//		const json11::Json generationDataJson = mesh->GetGenerationData();
//		auto genInfo = generationDataJson.dump();
//		insertCmd.bind(":genInfo", genInfo.c_str(), sqlite3pp::nocopy);
//		int res = insertCmd.execute();
//
//		if (res != SQLITE_OK)
//		{
//			const std::string errorMessage = db->error_msg();
//			Logger::Instance->error("Failed to create Mesh Scene Node: {}", errorMessage);
//			return false;
//		}
//
//		meshNode->SetEntityId(GetLastAutoincrementId());
//		meshNode->SetEntityState(DatabaseRecord::State::CLEAN);
//		return true;
//	}
//
//	return false;
//}

//bool GibEngine::World::Database::SavePointLight(Scene::Node* lightSceneNode)
//{
//	PointLight* pl = reinterpret_cast<PointLight*>(lightSceneNode->GetEntity());
//
//	switch (lightSceneNode->GetDatabaseRecord().GetEntityState())
//	{
//	case DatabaseRecord::State::CLEAN:
//		return true;
//	case DatabaseRecord::State::DIRTY:
//	{
//		sqlite3pp::command updateCmd(*db, DatabaseQuery::UPDATE_LIGHT_COMMAND.c_str());
//		updateCmd.bind(":id", lightSceneNode->GetDatabaseRecord().GetEntityId());
//		updateCmd.bind(":lightType", "PointLight", sqlite3pp::nocopy);
//
//		const std::string ambient = ConvertVec3ToString(pl->GetAmbientColor());
//		updateCmd.bind(":ambientColor", ambient, sqlite3pp::nocopy);
//
//		const std::string diffuse = ConvertVec3ToString(pl->GetDiffuseColor());
//		updateCmd.bind(":diffuseColor", diffuse, sqlite3pp::nocopy);
//
//		const std::string specular = ConvertVec3ToString(pl->GetSpecularColor());
//		updateCmd.bind(":specularColor", specular, sqlite3pp::nocopy);
//
//		updateCmd.bind(":linearAttenuation", pl->GetLinearAttenuation());
//		updateCmd.bind(":quadraticAttenuation", pl->GetQuadraticAttenuation());
//
//		int res = updateCmd.execute();
//		if (res != SQLITE_OK)
//		{
//			const std::string errorMessage = db->error_msg();
//			Logger::Instance->error("Failed to update PointLight Scene Node: {}", errorMessage);
//			return false;
//		}
//
//		lightSceneNode->SetEntityState(DatabaseRecord::State::CLEAN);
//		return true;
//	}
//	case DatabaseRecord::State::NEW:
//	{
//		sqlite3pp::command insertCmd(*db, DatabaseQuery::CREATE_LIGHT_COMMAND.c_str());
//		insertCmd.bind(":lightType", "PointLight", sqlite3pp::nocopy);
//
//		const std::string pos = ConvertVec3ToString(pl->GetPosition());
//		insertCmd.bind(":position", pos, sqlite3pp::nocopy);
//
//		const std::string ambient = ConvertVec3ToString(pl->GetAmbientColor());
//		insertCmd.bind(":ambientColor", ambient, sqlite3pp::nocopy);
//
//		const std::string diffuse = ConvertVec3ToString(pl->GetDiffuseColor());
//		insertCmd.bind(":diffuseColor", diffuse, sqlite3pp::nocopy);
//
//		const std::string specular = ConvertVec3ToString(pl->GetSpecularColor());
//		insertCmd.bind(":specularColor", specular, sqlite3pp::nocopy);
//
//		insertCmd.bind(":linearAttenuation", pl->GetLinearAttenuation());
//		insertCmd.bind(":quadraticAttenuation", pl->GetQuadraticAttenuation());
//
//		int res = insertCmd.execute();
//		if (res != SQLITE_OK)
//		{
//			const std::string errorMessage = db->error_msg();
//			Logger::Instance->error("Failed to save PointLight Scene Node: {}", errorMessage);
//			return false;
//		}
//
//		lightSceneNode->SetEntityId(GetLastAutoincrementId());
//		lightSceneNode->SetEntityState(DatabaseRecord::State::CLEAN);
//		return true;
//	}
//	}
//
//	return false;
//}
//
//bool GibEngine::World::Database::SaveSkybox(Scene::Node* skyboxSceneNode)
//{
//	Skybox* skybox = reinterpret_cast<Skybox*>(skyboxSceneNode->GetEntity());
//	
//	switch (skyboxSceneNode->GetDatabaseRecord().GetEntityState())
//	{
//	case DatabaseRecord::State::CLEAN:
//		return true;
//
//	case DatabaseRecord::State::DIRTY:
//	{
//		sqlite3pp::command updateCmd(*db, DatabaseQuery::UPDATE_SKYBOX_COMMAND.c_str());
//		updateCmd.bind(":id", skyboxSceneNode->GetDatabaseRecord().GetEntityId());
//		updateCmd.bind(":assetName", skybox->GetName(), sqlite3pp::copy);
//		//updateCmd.bind(":extension", skybox->GetExtension(), sqlite3pp::copy);
//		int res = updateCmd.execute();
//
//		if (res != SQLITE_OK)
//		{
//			const std::string errorMessage = db->error_msg();
//			Logger::Instance->error("Failed to update Skybox Scene Node: {}", errorMessage);
//			return false;
//		}
//
//		skyboxSceneNode->SetEntityState(DatabaseRecord::State::CLEAN);
//		return true;
//	}
//	case DatabaseRecord::State::NEW:
//	{
//		sqlite3pp::command insertCmd(*db, DatabaseQuery::CREATE_SKYBOX_COMMAND.c_str());
//		insertCmd.bind(":assetName", skybox->GetName().c_str(), sqlite3pp::copy);
//		insertCmd.bind(":extension", ""/*skybox->GetExtension().c_str()*/, sqlite3pp::nocopy);
//		int res = insertCmd.execute();
//
//		if (res != SQLITE_OK)
//		{
//			const std::string errorMessage = db->error_msg();
//			Logger::Instance->error("Failed to create Skybox Scene Node: {}", errorMessage);
//			return false;
//		}
//
//		skyboxSceneNode->SetEntityId(GetLastAutoincrementId());
//		skyboxSceneNode->SetEntityState(DatabaseRecord::State::CLEAN);
//		return true;
//	}
//	}
//  
//	return false;
//}
//
//bool GibEngine::World::Database::SaveSceneNode(int parentNodeId, Scene::Node* node)
//{
//	bool objectSaved = true;
//
//	// If this is a Flags::MESH_ROOT, handle it completely differently, out of laziness to design:
//	if (Scene::Node::FlagMask(node->GetFlags() & Scene::Node::Flags::MESH_ROOT))
//	{
//		// Save the Scene Node
//		if (node->GetChildNodeCount() > 0)
//		{
//			// Get the first child for the node, and extract the Entity
//			Scene::Node* meshEntityNode = *node->GetChildNodesBegin();
//
//			// Overwrite mesh flags with state from Entity State:
//			meshEntityNode->SetEntityState(node->GetDatabaseRecord().GetEntityState());
//
//			// Save the Entity
//			objectSaved = SaveEntity(meshEntityNode);
//
//			node->SetEntityId(meshEntityNode->GetDatabaseRecord().GetEntityId());
//			node->SetEntityState(World::DatabaseRecord::State::NEW);
//			
//			node->SetEntity(meshEntityNode->GetEntity());
//		}
//
//		SaveSceneNodeRecord(parentNodeId, node);
//		return true;
//	}
//	else if (node->GetEntity() != nullptr)
//	{
//		objectSaved = SaveEntity(node);
//	}
//
//	if (!objectSaved || !SaveSceneNodeRecord(parentNodeId, node))
//	{
//		// Bail here if we failed to save this object, it's children can't be saved.
//		return false;
//	}
//
//	for (std::vector<Scene::Node*>::const_iterator iter = node->GetChildNodesBegin(); iter != node->GetChildNodesEnd(); ++iter)
//	{
//		SaveSceneNode(node->GetDatabaseRecord().GetId(), *iter);
//	}
//	
//	return true;
//}
//
//bool GibEngine::World::Database::SaveSceneNodeRecord(int parentId, Scene::Node* node)
//{
//	switch (node->GetDatabaseRecord().GetState())
//	{
//	case DatabaseRecord::State::CLEAN:
//		return true;
//	case DatabaseRecord::State::DIRTY:
//	{
//		auto localTrans = node->GetLocalTransform();
//		glm::vec3 pos = glm::vec3(localTrans[3][0], localTrans[3][1], localTrans[3][2]);
//		glm::vec3 scale = glm::vec3(localTrans[0][0], localTrans[1][1], localTrans[2][2]);
//
//		sqlite3pp::command cmd(*db, DatabaseQuery::UPDATE_NODE_COMMAND.c_str());
//		cmd.bind(":id", node->GetDatabaseRecord().GetId());
//		cmd.bind(":parentId", parentId);
//
//		cmd.bind(":entityId", node->GetDatabaseRecord().GetEntityId());
//		
//		if (node->GetEntity() != nullptr)
//		{
//			cmd.bind(":entityType", node->GetEntity()->GetTypeName(), sqlite3pp::copy);
//		}
//		else if (node->GetChildNodeCount() > 0)
//		{
//			// Read the first node, and store that entity (Mesh etc.)
//			auto childNode = *node->GetChildNodesBegin();
//			if(childNode != nullptr)
//			{
//				cmd.bind(":entityType", childNode->GetEntity()->GetTypeName(), sqlite3pp::copy);
//			}
//		}
//
//		const std::string position = ConvertVec3ToString(pos);
//		cmd.bind(":position", position, sqlite3pp::nocopy);
//
//		const std::string scl = ConvertVec3ToString(scale);
//		cmd.bind(":scale", scl, sqlite3pp::nocopy);
//
//		int res = cmd.execute();
//
//		if (res != SQLITE_OK)
//		{
//			const char* errorMessage = db->error_msg();
//			Logger::Instance->error("Failed to update Scene Node Record: {}", errorMessage);
//			return false;
//		}
//
//		node->SetNodeState(DatabaseRecord::State::CLEAN);
//		return true;
//	}
//	case DatabaseRecord::State::DELETED:
//	{
//		sqlite3pp::command cmd(*db, DatabaseQuery::DELETE_NODE_COMMAND.c_str());
//		cmd.bind(":id", node->GetDatabaseRecord().GetId());
//
//		int res = cmd.execute();
//
//		if (res != SQLITE_OK)
//		{
//			const std::string errorMessage = db->error_msg();
//			Logger::Instance->error("Failed to delete Scene Node Record: {}", errorMessage);
//			return false;
//		}
//
//		return true;
//	}
//	case DatabaseRecord::State::NEW:
//	{
//		auto localTrans = node->GetLocalTransform();
//		glm::vec3 pos = glm::vec3(localTrans[3][0], localTrans[3][1], localTrans[3][2]);
//		glm::vec3 scale = glm::vec3(localTrans[0][0], localTrans[1][1], localTrans[2][2]);
//
//		sqlite3pp::command cmd(*db, DatabaseQuery::CREATE_NODE_COMMAND.c_str());
//		cmd.bind(":parentId", parentId);
//
//		if (node->GetEntity() != nullptr)
//		{
//			cmd.bind(":entityType", node->GetEntity()->GetTypeName(), sqlite3pp::copy);
//			cmd.bind(":entityId", node->GetDatabaseRecord().GetEntityId());
//		}
//
//		const std::string position = ConvertVec3ToString(pos);
//		cmd.bind(":position", position, sqlite3pp::nocopy);
//
//		const std::string scl = ConvertVec3ToString(scale);
//		cmd.bind(":scale", scl, sqlite3pp::nocopy);
//
//		int res = cmd.execute();
//
//		if (res != SQLITE_OK)
//		{
//			const char* errorMessage = db->error_msg();
//			Logger::Instance->error("Failed to save Scene Node Record: {}", errorMessage);
//			return false;
//		}
//
//		node->SetNodeId(GetLastAutoincrementId());
//		node->SetNodeState(DatabaseRecord::State::CLEAN);
//		return true;
//	}
//	}
//	return false;
//}
//
//bool GibEngine::World::Database::SaveEntity(GibEngine::Scene::Node* entityNode)
//{
//	Entity* entity = entityNode->GetEntity();
//
//	switch (entity->GetType())
//	{
//	case Entity::Type::SKYBOX:
//		return SaveSkybox(entityNode);
//	case Entity::Type::POINT_LIGHT:
//		return SavePointLight(entityNode);
//	case Entity::Type::MESH:
//		return SaveMesh(entityNode);
//	default:
//		return false;
//	}
//}

int GibEngine::World::Database::GetLastAutoincrementId()
{
    sqlite3pp::query qry(*db, DatabaseQuery::SELECT_LAST_AUTOINCREMENT_ID.c_str());

    sqlite3pp::query::iterator iter = qry.begin();
    int id = (*iter).get<int>(0);
    
    return id;
}

//GibEngine::Scene::Node* GibEngine::World::Database::FindNode(int nodeId)
//{
//	sqlite3pp::query qry(*db, DatabaseQuery::SELECT_NODE_QUERY.c_str());
//	qry.bind(":id", nodeId);
//
//	for (auto iter = qry.begin(); iter != qry.end(); ++iter)
//	{
//		int parentId, entityId;
//		const char* entityType;
//		const char* position;
//		const char* scale;
//
//		std::tie(parentId, entityType, entityId, position, scale) =
//			(*iter).get_columns<int, const char*, int, const char*, const char*>(0, 1, 2, 3, 4);
//
//		Scene::Node* node;
//		glm::mat4 nodeTransform;
//		nodeTransform = glm::translate(nodeTransform, ReadVec3(position));
//		nodeTransform = glm::scale(nodeTransform, ReadVec3(scale));
//
//		if (entityType != nullptr)
//		{
//			if (strcmp(entityType, Entity::GetTypeString(Entity::Type::SKYBOX).c_str()) == 0)
//			{
//				node = new Scene::Node(Entity::GetTypeString(Entity::Type::SKYBOX));
//				node->SetEntity(LoadSkybox(entityId));
//				node->SetEntityId(entityId);
//			}
//			else if (strcmp(entityType, "Mesh") == 0)
//			{				
//				node = LoadMesh(entityId);
//				node->SetEntityId(entityId);
//			}
//			else if (strcmp(entityType, "Point Light") == 0)
//			{
//				node = new Scene::Node("Point Light");
//				node->SetEntity(LoadLight(entityId));
//				node->SetEntityId(entityId);
//
//				if (debugMode)
//				{
//					// Attach the sphere mesh 
//
//		/*			auto sphereNode = MeshService::Load(graphicsApi, fileSystem->GetWorkingDirectory() + "/../../Assets/Models/default/sphere/sphere.obj", forwardGenerationData);
//					pointLightNode->AddChildNode(sphereNode);*/
//				}
//			}
//			else
//			{
//				Logger::Instance->error("Failed to parse Scene Node type `{}`, no loader available.", entityType);
//				continue;
//			}
//		}
//		else
//		{
//			node = new Scene::Node("Transform Node");
//		}
//		
//		node->SetNodeId(nodeId);
//		node->SetNodeState(DatabaseRecord::State::CLEAN);
//
//		node->SetLocalTransform(nodeTransform);
//
//		// Load all child nodes:
//		sqlite3pp::query childNodeQry(*db, DatabaseQuery::SELECT_CHILD_NODES_QUERY.c_str());
//		childNodeQry.bind(":parentId", nodeId);
//
//		for (auto childIter = childNodeQry.begin(); childIter != childNodeQry.end(); ++childIter)
//		{
//			int childNodeId = (*childIter).get<int>(0);
//			node->AddChildNode(FindNode(childNodeId));
//		}
//
//		return node;
//	}
//
//	return nullptr;
//}

std::string GibEngine::World::Database::ConvertVec3ToString(const glm::vec3& vec)
{
	std::string str;
	for (int i = 0; i < 3; i++)
	{
		str += std::to_string(vec[i]) + ", ";
	}

	return str;
}

glm::vec3 GibEngine::World::Database::ReadVec3(std::string vec3String)
{
	if (vec3String.length() == 0)
	{
		return glm::vec3();
	}

	size_t pos = 0;
	int idx = 0;
    glm::vec3 vec = glm::vec3();
	while ((pos = vec3String.find(',')) != vec3String.npos)
	{
		if (idx >= 3)
		{
			break;
		}

		vec[idx++] = std::stof(vec3String.substr(0, pos));
		vec3String.erase(0, pos+1);

	}

    return vec;
}