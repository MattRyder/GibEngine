#include "world/Database.h"

GibEngine::World::Database::Database(const char* databaseFilepath)
{
    std::ifstream dbFile(databaseFilepath);
    bool dbExists = dbFile.good();

    db = new sqlite3pp::database(databaseFilepath);

    if(!dbExists)
    {
        int res = db->execute(CREATE_DATABASE_COMMAND);
    
        if(res != SQLITE_OK)
        {
            const char* errorMessage = db->error_msg();
            Logger::Instance->error("Failed to create WorldDb: {}", errorMessage);
        }
    }
}

GibEngine::World::Database::~Database()
{
	Disconnect();
	delete db;
}

void GibEngine::World::Database::Disconnect()
{
	db->disconnect();
}

bool GibEngine::World::Database::CreateLevel(int rootNodeId, const char* name)
{
    sqlite3pp::command insertCmd(*db, CREATE_LEVEL_COMMAND);
	insertCmd.bind(":nodeId", rootNodeId);
	insertCmd.bind(":name", name, sqlite3pp::nocopy);
    int res = insertCmd.execute();

    if(res != SQLITE_OK)
    {
        const char* errorMessage = db->error_msg();
        Logger::Instance->error("Failed to create WorldDb Level! SQLite Error: {}", errorMessage);
		return false;
    } 

	return true;
}

GibEngine::Skybox* GibEngine::World::Database::LoadSkybox(int skyboxId)
{
	sqlite3pp::query qry(*db, SELECT_SKYBOX_QUERY);
	qry.bind(":id", skyboxId);

	for (auto iter = qry.begin(); iter != qry.end(); ++iter)
	{
		const char* assetName;
		const char* extension;

		std::tie(assetName, extension) = (*iter).get_columns<const char*, const char*>(0, 1);

		Skybox* skybox = new Skybox(strdup(assetName), strdup(extension));
		return skybox;
	}

	return nullptr;
}

GibEngine::PointLight* GibEngine::World::Database::LoadLight(int lightId)
{
	sqlite3pp::query qry(*db, SELECT_LIGHT_QUERY);
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

GibEngine::Scene::Node* GibEngine::World::Database::LoadMesh(int meshId)
{
	sqlite3pp::query qry(*db, SELECT_MESH_QUERY);
	qry.bind(":id", meshId);

	for (auto iter = qry.begin(); iter != qry.end(); ++iter)
	{
		const char* assetName = (*iter).get<const char*>(0);

		File* meshAssetFile = File::GetModelFile(assetName);
		return MeshService::Load(meshAssetFile);
	}

	return nullptr;
}

GibEngine::Scene::Node* GibEngine::World::Database::LoadLevel(int rootNodeId)
{
	return FindNode(rootNodeId);
}

bool GibEngine::World::Database::SaveLevel(Scene::Node* sceneRootNode)
{
	return SaveSceneNode(0, sceneRootNode);
}

bool GibEngine::World::Database::SaveMesh(Scene::Node* meshNode)
{
	Mesh* mesh = reinterpret_cast<Mesh*>(meshNode->GetEntity());

	switch (meshNode->GetDatabaseRecord()->GetState())
	{
	case DatabaseRecord::State::CLEAN:
		return true;
	case DatabaseRecord::State::DIRTY:
		return false;
	case DatabaseRecord::State::NEW:
		sqlite3pp::command insertCmd(*db, CREATE_MESH_COMMAND);
		insertCmd.bind(":assetName", mesh->GetOwnerAssetName(), sqlite3pp::nocopy);
		int res = insertCmd.execute();

		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to create Mesh Scene Node: {}", errorMessage);
			return false;
		}

		meshNode->GetDatabaseRecord()->SetAttachedEntityId(GetLastAutoincrementId());
		meshNode->GetDatabaseRecord()->SetEntityState(DatabaseRecord::State::CLEAN);
		return true;
	}

	return false;
}

bool GibEngine::World::Database::SavePointLight(Scene::Node* lightSceneNode)
{
	PointLight* pl = reinterpret_cast<PointLight*>(lightSceneNode->GetEntity());

	switch (lightSceneNode->GetDatabaseRecord()->GetState())
	{
	case DatabaseRecord::State::CLEAN:
		return true;
	case DatabaseRecord::State::DIRTY:
	{
		//sqlite3pp::command updateCmd(*db, UPDATE_LIGHT_QUERY);
		//updateCmd.bind(":id", lightSceneNode->GetDatabaseRecord()->GetId());
		//updateCmd.bind(":lightType", "PointLight", sqlite3pp::nocopy);

		//const std::string ambient = ConvertVec3ToString(pl->GetAmbientColor());
		//updateCmd.bind(":ambientColor", ambient, sqlite3pp::nocopy);

		//const std::string diffuse = ConvertVec3ToString(pl->GetDiffuseColor());
		//updateCmd.bind(":diffuseColor", diffuse, sqlite3pp::nocopy);

		//const std::string specular = ConvertVec3ToString(pl->GetSpecularColor());
		//updateCmd.bind(":specularColor", specular, sqlite3pp::nocopy);

		//updateCmd.bind(":linearAttenuation", pl->GetLinearAttenuation());
		//updateCmd.bind(":quadraticAttenuation", pl->GetQuadraticAttenuation());

		//int res = updateCmd.execute();
		//if (res != SQLITE_OK)
		//{
		//	const char* errorMessage = db->error_msg();
		//	Logger::Instance->error("Failed to update PointLight Scene Node: {}", errorMessage);
		//	return false;
		//}

		return true;
	}
	case DatabaseRecord::State::NEW:
	{
		sqlite3pp::command insertCmd(*db, CREATE_LIGHT_COMMAND);
		insertCmd.bind(":lightType", "PointLight", sqlite3pp::nocopy);

		const std::string pos = ConvertVec3ToString(pl->GetPosition());
		insertCmd.bind(":position", pos, sqlite3pp::nocopy);

		const std::string ambient = ConvertVec3ToString(pl->GetAmbientColor());
		insertCmd.bind(":ambientColor", ambient, sqlite3pp::nocopy);

		const std::string diffuse = ConvertVec3ToString(pl->GetDiffuseColor());
		insertCmd.bind(":diffuseColor", diffuse, sqlite3pp::nocopy);

		const std::string specular = ConvertVec3ToString(pl->GetSpecularColor());
		insertCmd.bind(":specularColor", specular, sqlite3pp::nocopy);

		insertCmd.bind(":linearAttenuation", pl->GetLinearAttenuation());
		insertCmd.bind(":quadraticAttenuation", pl->GetQuadraticAttenuation());

		int res = insertCmd.execute();
		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to save PointLight Scene Node: {}", errorMessage);
			return false;
		}

		lightSceneNode->GetDatabaseRecord()->SetAttachedEntityId(GetLastAutoincrementId());
		lightSceneNode->GetDatabaseRecord()->SetEntityState(DatabaseRecord::State::CLEAN);
		return true;
	}
	}

	return false;
}

bool GibEngine::World::Database::SaveSkybox(Scene::Node* skyboxSceneNode)
{
	auto dbRecord = skyboxSceneNode->GetDatabaseRecord();
	Skybox* skybox = reinterpret_cast<Skybox*>(skyboxSceneNode->GetEntity());
	
	switch (skyboxSceneNode->GetDatabaseRecord()->GetEntityState())
	{
	case DatabaseRecord::State::CLEAN:
		return true;

	case DatabaseRecord::State::DIRTY:
	{
		sqlite3pp::command updateCmd(*db, UPDATE_SKYBOX_COMMAND);
		updateCmd.bind(":assetName", skybox->GetName(), sqlite3pp::nocopy);
		updateCmd.bind(":extension", skybox->GetExtension(), sqlite3pp::nocopy);
		int res = updateCmd.execute();

		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to update Skybox Scene Node: {}", errorMessage);
			return false;
		}

		dbRecord->SetEntityState(DatabaseRecord::State::CLEAN);
		return true;
	}
	case DatabaseRecord::State::NEW:
	{
		sqlite3pp::command insertCmd(*db, CREATE_SKYBOX_COMMAND);
		insertCmd.bind(":assetName", skybox->GetName(), sqlite3pp::nocopy);
		insertCmd.bind(":extension", skybox->GetExtension(), sqlite3pp::nocopy);
		int res = insertCmd.execute();

		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to create Skybox Scene Node: {}", errorMessage);
			return false;
		}

		dbRecord->SetAttachedEntityId(GetLastAutoincrementId());
		dbRecord->SetEntityState(DatabaseRecord::State::CLEAN);
		return true;
	}
	}
  
	return false;
}

bool GibEngine::World::Database::SaveSceneNode(int parentNodeId, Scene::Node* node)
{
	bool objectSaved = true;

	if (node->GetEntity() != nullptr)
	{
		Entity* entityBase = node->GetEntity();

		switch (entityBase->GetType())
		{
		case EntityType::SKYBOX:
			objectSaved = SaveSkybox(node);
			break;
		case EntityType::POINT_LIGHT:
			objectSaved = SavePointLight(node);
			break;
		case EntityType::MESH:
			objectSaved = SaveMesh(node);
			break;
		default:
			objectSaved = false;
			break;
		}
	}
	
	if (!objectSaved || !SaveSceneNodeRecord(parentNodeId, node))
	{
		// Bail here if we failed to save this object, it's children can't be saved.
		return false;
	}

	for (std::vector<Scene::Node*>::const_iterator iter = node->GetChildNodesBegin(); iter != node->GetChildNodesEnd(); ++iter)
	{
		SaveSceneNode(node->GetDatabaseRecord()->GetId(), *iter);
	}
	
	return true;
}

bool GibEngine::World::Database::SaveSceneNodeRecord(int parentId, Scene::Node* node)
{
	switch (node->GetDatabaseRecord()->GetState())
	{
	case DatabaseRecord::State::CLEAN:
		return true;
	case DatabaseRecord::State::DIRTY:
	{
		auto localTrans = node->GetLocalTransform();
		glm::vec3 pos = glm::vec3(localTrans[3][0], localTrans[3][1], localTrans[3][2]);
		glm::vec3 scale = glm::vec3(localTrans[0][0], localTrans[1][1], localTrans[2][2]);

		sqlite3pp::command cmd(*db, UPDATE_NODE_COMMAND);
		cmd.bind(":id", node->GetDatabaseRecord()->GetId());
		cmd.bind(":parentId", parentId);

		if (node->GetEntity() != nullptr)
		{
			cmd.bind(":entityType", node->GetEntity()->GetTypeName(), sqlite3pp::nocopy);
			cmd.bind(":entityId", node->GetDatabaseRecord()->GetEntityId());
		}

		const std::string position = ConvertVec3ToString(pos);
		cmd.bind(":position", position, sqlite3pp::nocopy);

		const std::string scl = ConvertVec3ToString(scale);
		cmd.bind(":scale", scl, sqlite3pp::nocopy);

		int res = cmd.execute();

		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to update Scene Node Record: {}", errorMessage);
			return false;
		}

		node->GetDatabaseRecord()->SetState(DatabaseRecord::State::CLEAN);
		return true;
	}
	case DatabaseRecord::State::DELETED:
	{
		sqlite3pp::command cmd(*db, DELETE_NODE_COMMAND);
		cmd.bind(":id", node->GetDatabaseRecord()->GetId());

		int res = cmd.execute();

		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to delete Scene Node Record: {}", errorMessage);
			return false;
		}

		return true;
	}
	case DatabaseRecord::State::NEW:
	{
		auto localTrans = node->GetLocalTransform();
		glm::vec3 pos = glm::vec3(localTrans[3][0], localTrans[3][1], localTrans[3][2]);
		glm::vec3 scale = glm::vec3(localTrans[0][0], localTrans[1][1], localTrans[2][2]);

		sqlite3pp::command cmd(*db, CREATE_NODE_COMMAND);
		cmd.bind(":parentId", parentId);

		if (node->GetEntity() != nullptr)
		{
			cmd.bind(":entityType", node->GetEntity()->GetTypeName(), sqlite3pp::nocopy);
			cmd.bind(":entityId", node->GetDatabaseRecord()->GetEntityId());
		}

		const std::string position = ConvertVec3ToString(pos);
		cmd.bind(":position", position, sqlite3pp::nocopy);

		const std::string scl = ConvertVec3ToString(scale);
		cmd.bind(":scale", scl, sqlite3pp::nocopy);

		int res = cmd.execute();

		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to save Scene Node Record: {}", errorMessage);
			return false;
		}

		node->GetDatabaseRecord()->SetId(GetLastAutoincrementId());
		node->GetDatabaseRecord()->SetState(DatabaseRecord::State::CLEAN);
		return true;
	}
	}
	return false;
}

int GibEngine::World::Database::GetLastAutoincrementId()
{
    sqlite3pp::query qry(*db, SELECT_LAST_AUTOINCREMENT_ID);

    sqlite3pp::query::iterator iter = qry.begin();
    int id = (*iter).get<int>(0);
    
    return id;
}

GibEngine::Scene::Node* GibEngine::World::Database::FindNode(int nodeId)
{
	sqlite3pp::query qry(*db, SELECT_NODE_QUERY);
	qry.bind(":id", nodeId);

	for (auto iter = qry.begin(); iter != qry.end(); ++iter)
	{
		int parentId, entityId;
		const char* entityType;
		const char* position;
		const char* scale;

		std::tie(parentId, entityType, entityId, position, scale) =
			(*iter).get_columns<int, const char*, int, const char*, const char*>(0, 1, 2, 3, 4);

		Scene::Node* node;
		glm::mat4 nodeTransform;
		nodeTransform = glm::translate(nodeTransform, ReadVec3(position));
		nodeTransform = glm::scale(nodeTransform, ReadVec3(scale));

		if (entityType != nullptr)
		{
			if (strcmp(entityType, "Skybox") == 0)
			{
				node = new Scene::Node("Skybox");
				node->SetEntity(LoadSkybox(entityId));
				node->GetDatabaseRecord()->SetAttachedEntityId(entityId);
			}
			else if (strcmp(entityType, "Mesh") == 0)
			{				
				node = LoadMesh(entityId);
				node->GetDatabaseRecord()->SetAttachedEntityId(entityId);
			}
			else if (strcmp(entityType, "Point Light") == 0)
			{
				node = new Scene::Node("Point Light");
				node->SetEntity(LoadLight(entityId));
				node->GetDatabaseRecord()->SetAttachedEntityId(entityId);
			}
			else
			{
				continue;
			}
		}
		else
		{
			node = new Scene::Node("Transform Node");
		}
		
		node->GetDatabaseRecord()->SetId(nodeId);
		node->GetDatabaseRecord()->SetState(DatabaseRecord::State::CLEAN);

		node->SetLocalTransform(nodeTransform);

		// Load all child nodes:
		sqlite3pp::query childNodeQry(*db, SELECT_CHILD_NODES_QUERY);
		childNodeQry.bind(":parentId", nodeId);

		for (auto childIter = childNodeQry.begin(); childIter != childNodeQry.end(); ++childIter)
		{
			int childNodeId = (*childIter).get<int>(0);
			node->AddChildNode(FindNode(childNodeId));
		}

		return node;
	}

	return nullptr;
}

std::string GibEngine::World::Database::ConvertVec3ToString(glm::vec3 vec)
{
	std::string str;
	for (int i = 0; i < 3; i++)
	{
		str += std::to_string(vec[i]) + ", ";
	}

	return str;
}

glm::vec3 GibEngine::World::Database::ReadVec3(const char* vec3String)
{
	if (std::string(vec3String).size() == 0)
	{
		return glm::vec3();
	}

    char* mutVec3Str = strdup(vec3String);                
    char* value = std::strtok(mutVec3Str, ",");

    glm::vec3 vec = glm::vec3();
    for(int i = 0; i < 3; i++)
    {                   
        vec[i] = std::stof(std::string(value));
        value = std::strtok(NULL, ",");
    }

    return vec;
}