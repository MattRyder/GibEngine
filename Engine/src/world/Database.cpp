#include "world/Database.h"

GibEngine::World::Database::Database(const char* databaseFilepath)
{
    std::ifstream dbFile(databaseFilepath);
    bool dbExists = dbFile.good();

    db = new sqlite3pp::database(databaseFilepath);

    if(!dbExists)
    {
        int res = db->execute(CREATE_DATABASE_QUERY);
    
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

GibEngine::World::Level* GibEngine::World::Database::CreateLevel(const char* levelName)
{
    sqlite3pp::command insertCmd(*db, CREATE_LEVEL_QUERY);
    insertCmd.bind(":levelName", levelName, sqlite3pp::nocopy);
    int res = insertCmd.execute();

    if(res != SQLITE_OK)
    {
        const char* errorMessage = db->error_msg();
        Logger::Instance->error("Failed to create WorldDb Level! SQLite Error: {}", errorMessage);
        return nullptr;
    } 

    return new Level(GetLastAutoincrementId(), levelName);
}

bool GibEngine::World::Database::SaveLevel(Level* level)
{
    int levelId = level->GetId();

	// Save Skybox if entity is present and requires a write:
	if (level->GetSkyboxEntity() != nullptr && level->GetSkyboxEntity()->GetState() != DatabaseEntityState::CLEAN)
	{
		int skyboxId = SaveSkybox(level->GetSkyboxEntity());
		if (skyboxId == -1)
		{
			Logger::Instance->error("Failed to set Level Skybox! {}", level->GetSkyboxEntity()->GetEntity()->GetName());
			return false;
		}
		SetLevelSkybox(levelId, skyboxId);
	}

	// Save each of the model entities in the level:
    for(auto model : level->GetModelEntities())
    {
        if(!SaveModel(levelId, model))
        {
            Logger::Instance->error("Failed to create WorldDb Model! {}", model->GetEntity()->GetAssetName());
            return false;
        }

        for(auto modelInstance : model->GetEntity()->GetModelInstances())
        {
			if (!SaveInstance(model->GetId(), modelInstance))
			{
				Logger::Instance->info("Failed to save ModelInstance for Model: {}", model->GetEntity()->GetAssetName());
			}
        }
    }

	for (auto pointLight : level->GetPointLightEntities())
	{
		if (!SavePointLight(levelId, pointLight))
		{
			Logger::Instance->error("Failed to save PointLight! {}", pointLight->GetEntity()->GetName());
			return false;
		}
	}

    return true;
}

bool GibEngine::World::Database::SaveModel(int levelId, GibEngine::World::DatabaseEntity<Model>* model)
{
	switch (model->GetState())
	{
	case DatabaseEntityState::CLEAN:
		return true;
	case DatabaseEntityState::DIRTY:
		return false;
	case DatabaseEntityState::NEW:
		sqlite3pp::command insertCmd(*db, CREATE_MODEL_QUERY);
		std::string levelIdStr = std::to_string(levelId);
		insertCmd.bind(":levelId", levelIdStr.c_str(), sqlite3pp::nocopy);
		insertCmd.bind(":assetName", model->GetEntity()->GetAssetName(), sqlite3pp::nocopy);
		int res = insertCmd.execute();

		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to create WorldDb Model! SQLite Error: {}", errorMessage);
			return false;
		}

		model->SetId(GetLastAutoincrementId());
		model->SetState(DatabaseEntityState::CLEAN);
		return true;
	}

	return false;
}

bool GibEngine::World::Database::SavePointLight(int levelId, DatabaseEntity<PointLight>* pointLight)
{
	switch (pointLight->GetState())
	{
	case DatabaseEntityState::CLEAN:
		return true;
	case DatabaseEntityState::DIRTY:
	{
		sqlite3pp::command updateCmd(*db, UPDATE_LIGHT_QUERY);
		auto pl = pointLight->GetEntity();
		const std::string lightId = std::to_string(pointLight->GetId());
		updateCmd.bind(":id", lightId.c_str(), sqlite3pp::nocopy);
		updateCmd.bind(":lightType", "PointLight", sqlite3pp::nocopy);

		const std::string pos = ConvertVec3ToString(pl->GetPosition());
		updateCmd.bind(":position", pos, sqlite3pp::nocopy);

		const std::string ambient = ConvertVec3ToString(pl->GetAmbientColor());
		updateCmd.bind(":ambientColor", ambient, sqlite3pp::nocopy);

		const std::string diffuse = ConvertVec3ToString(pl->GetDiffuseColor());
		updateCmd.bind(":diffuseColor", diffuse, sqlite3pp::nocopy);

		const std::string specular = ConvertVec3ToString(pl->GetSpecularColor());
		updateCmd.bind(":specularColor", specular, sqlite3pp::nocopy);

		const std::string linearAtten = std::to_string(pl->GetLinearAttenuation());
		updateCmd.bind(":linearAttenuation", linearAtten, sqlite3pp::nocopy);

		const std::string quadraticAtten = std::to_string(pl->GetQuadraticAttenuation());
		updateCmd.bind(":quadraticAttenuation", quadraticAtten, sqlite3pp::nocopy);

		int res = updateCmd.execute();
		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to update Point Light! SQLite Error: {}", errorMessage);
			return false;
		}

		pointLight->SetState(DatabaseEntityState::CLEAN);
		return true;
	}
	case DatabaseEntityState::NEW:
	{
		sqlite3pp::command insertCmd(*db, CREATE_LIGHT_QUERY);
		std::string levelIdStr = std::to_string(levelId);

		auto pl = pointLight->GetEntity();
		insertCmd.bind(":levelId", levelIdStr.c_str(), sqlite3pp::nocopy);
		insertCmd.bind(":lightType", "PointLight", sqlite3pp::nocopy);

		const std::string pos = ConvertVec3ToString(pl->GetPosition());
		insertCmd.bind(":position", pos, sqlite3pp::nocopy);

		const std::string ambient = ConvertVec3ToString(pl->GetAmbientColor());
		insertCmd.bind(":ambientColor", ambient, sqlite3pp::nocopy);

		const std::string diffuse = ConvertVec3ToString(pl->GetDiffuseColor());
		insertCmd.bind(":diffuseColor", diffuse, sqlite3pp::nocopy);

		const std::string specular = ConvertVec3ToString(pl->GetPosition());
		insertCmd.bind(":specularColor", specular, sqlite3pp::nocopy);

		const std::string linearAtten = std::to_string(pl->GetLinearAttenuation());
		insertCmd.bind(":linearAttenuation", linearAtten, sqlite3pp::nocopy);

		const std::string quadraticAtten = std::to_string(pl->GetQuadraticAttenuation());
		insertCmd.bind(":quadraticAttenuation", quadraticAtten, sqlite3pp::nocopy);

		int res = insertCmd.execute();
		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to save Point Light! SQLite Error: {}", errorMessage);
			return false;
		}

		pointLight->SetId(GetLastAutoincrementId());
		pointLight->SetState(DatabaseEntityState::CLEAN);
		return true;
	}
	}

	return false;
}

bool GibEngine::World::Database::SaveSkybox(World::DatabaseEntity<Skybox>* skybox)
{
	switch (skybox->GetState())
	{
	case DatabaseEntityState::CLEAN:
		return true;
	case DatabaseEntityState::DIRTY:
		return false; // not implemented yet
	case DatabaseEntityState::NEW:
		sqlite3pp::command insertCmd(*db, CREATE_SKYBOX_QUERY);
		insertCmd.bind(":assetName", skybox->GetEntity()->GetName(), sqlite3pp::nocopy);
		insertCmd.bind(":extension", skybox->GetEntity()->GetExtension(), sqlite3pp::nocopy);
		int res = insertCmd.execute();

		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to create WorldDb Skybox! SQLite Error: {}", errorMessage);
			return false;
		}

		skybox->SetId(GetLastAutoincrementId());
		skybox->SetState(DatabaseEntityState::CLEAN);
		return true;
	}
  
	return false;
}

int GibEngine::World::Database::SaveInstance(int modelId, glm::vec3 position, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 scale)
{
    sqlite3pp::command insertCmd(*db, CREATE_INSTANCE_QUERY);
	std::string modelIdStr = std::to_string(modelId);
    insertCmd.bind(":modelId", modelIdStr.c_str(), sqlite3pp::nocopy);

	if (rotationAngle != 0.0f)
	{
		std::string rotationAn = std::to_string(rotationAngle);
		insertCmd.bind(":rotationAngle", rotationAn.c_str(), sqlite3pp::nocopy);
	}

    std::string positionStr = std::string();
    std::string scaleStr = std::string();
    std::string rotationAxisStr = std::string();
    for(int i = 0; i < 3; i++)
    {
        positionStr += std::to_string(position[i]) + ", ";
        rotationAxisStr += std::to_string(rotationAxis[i]) + ", ";
        scaleStr += std::to_string(scale[i]) + ", ";
    }
    insertCmd.bind(":position", positionStr, sqlite3pp::nocopy);    
    insertCmd.bind(":rotationAxis", rotationAxisStr.c_str(), sqlite3pp::nocopy);
    if(glm::length(scale) > 0)
    {
        insertCmd.bind(":scale", scaleStr.c_str(), sqlite3pp::nocopy);        
    }

    int res = insertCmd.execute();

    if(res != SQLITE_OK)
    {
        const char* errorMessage = db->error_msg();
        Logger::Instance->error("Failed to save Model Instance! SQLite Error: {}", errorMessage);
        return -1;
    }

    return GetLastAutoincrementId();
}

bool GibEngine::World::Database::UpdateInstance(int modelId, GibEngine::World::DatabaseEntity<Mesh::Instance>* meshInstance)
{
	sqlite3pp::command updateCmd(*db, UPDATE_MODEL_INSTANCES_QUERY);
	
	updateCmd.bind(":rotationAngle", "", sqlite3pp::nocopy);

	std::string positionStr = std::string();
	std::string scaleStr = std::string();
	std::string rotationAxisStr = std::string();
	for (int i = 0; i < 3; i++)
	{
		positionStr += std::to_string(meshInstance->GetEntity()->GetPosition()[i]) + ", ";
		//rotationAxisStr += std::to_string(rotationAxis[i]) + ", ";
		scaleStr += std::to_string(meshInstance->GetEntity()->GetScale()[i]) + ", ";
	}

	updateCmd.bind(":position", positionStr, sqlite3pp::nocopy);
	updateCmd.bind(":rotationAxis", rotationAxisStr, sqlite3pp::nocopy);
	if (glm::length(meshInstance->GetEntity()->GetScale()) > 0)
	{
		updateCmd.bind(":scale", scaleStr, sqlite3pp::nocopy);
	}

	unsigned int id = meshInstance->GetId();
	std::string idStr = std::to_string(meshInstance->GetId());
	updateCmd.bind(":id", idStr.c_str(), sqlite3pp::nocopy);

	int res = updateCmd.execute();

	if (res != SQLITE_OK)
	{
		const char* errorMessage = db->error_msg();
		Logger::Instance->error("Failed to update Model Instance! SQLite Error: {}", errorMessage);
		return false;
	}

	return true;
}

bool GibEngine::World::Database::DeleteInstance(World::DatabaseEntity<Mesh::Instance>* meshInstance)
{
	switch (meshInstance->GetState())
	{
	case DatabaseEntityState::NEW:
		return true;
	default:
		sqlite3pp::command deleteCmd(*db, MODEL_INSTANCE_DELETE_QUERY);
		std::string idStr = std::to_string(meshInstance->GetId());
		deleteCmd.bind(":id", idStr.c_str(), sqlite3pp::nocopy);

		int res = deleteCmd.execute();

		if (res != SQLITE_OK)
		{
			const char* errorMessage = db->error_msg();
			Logger::Instance->error("Failed to delete Model Instance! SQLite Error: {}", errorMessage);
			return false;
		}

		return true;
	}
}

bool GibEngine::World::Database::SaveInstance(int modelId, World::DatabaseEntity<Mesh::Instance>* meshInstance)
{
	switch (meshInstance->GetState())
	{
	case DatabaseEntityState::CLEAN:
		return true;
	case DatabaseEntityState::DIRTY:
		return UpdateInstance(modelId, meshInstance);
	case DatabaseEntityState::DELETED:
		return DeleteInstance(meshInstance);
	case DatabaseEntityState::NEW:
		auto modelMatrix = meshInstance->GetEntity()->GetMatrix();
		glm::vec3 pos = glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
		glm::vec3 scale = glm::vec3(modelMatrix[0][0], modelMatrix[1][1], modelMatrix[2][2]);
		int instanceId = SaveInstance(modelId, pos, glm::vec3(), 0.0f, scale);
		if (instanceId == -1)
		{
			Logger::Instance->error("Failed to create WorldDb Model Instance");
			return false;
		}

		meshInstance->SetId(instanceId);
		meshInstance->SetState(DatabaseEntityState::CLEAN);
		return true;
	}
	return false;
}

GibEngine::World::Level* GibEngine::World::Database::FindLevel(int id)
{
    int levelId, skyboxId;
    const char* levelName, *skyboxName, *skyboxExt;

    sqlite3pp::query qry(*db, SELECT_LEVEL_QUERY);
    qry.bind(1, id);
    sqlite3pp::query::iterator iter = qry.begin();
    
    std::tie(levelId, levelName, skyboxId, skyboxName, skyboxExt) =
        (*iter).get_columns<int, const char*, int, const char*, const char*>(0, 1, 2, 3, 4);

    if(levelId > 0)
    {
        Level* level = new Level(levelId, strdup(levelName));

        if(skyboxName != nullptr && skyboxExt != nullptr)
        {
            Skybox* skybox = new Skybox(skyboxName, skyboxExt);
			DatabaseEntity<Skybox>* skyboxDbEntity = new DatabaseEntity<Skybox>(skyboxId, skybox);

            level->SetSkybox(skyboxDbEntity);
        }        
        
		// Load the models:
        sqlite3pp::query mQry(*db, SELECT_LEVEL_MODELS_QUERY);
        mQry.bind(1, levelId);

        for(auto mIter = mQry.begin(); mIter != mQry.end(); ++mIter)
        {
            int modelId;
            const char* assetName;
            std::tie(modelId, assetName) = (*mIter).get_columns<int, const char*>(0, 1);

            Model* model = new Model(assetName);

            sqlite3pp::query iQry(*db, SELECT_MODEL_INSTANCES_QUERY);
            iQry.bind(1, modelId);

            for(auto iIter = iQry.begin(); iIter != iQry.end(); ++iIter)
            {
				int instanceId = 0;
                const char* position;
                const char* rotationAxis;
                const char* rotationAngle;
                const char* scale;

                std::tie(instanceId, position, rotationAxis, rotationAngle, scale) =
                (*iIter).get_columns<int, const char*, const char*, const char*, const char*>(0, 1, 2, 3, 4);   

                glm::vec3 vecPosition = (position != nullptr) ? ReadVec3(position) : glm::vec3();
                glm::vec3 vecRotationAxis = (rotationAxis != nullptr) ? ReadVec3(rotationAxis) : glm::vec3();
                glm::vec3 vecScale = (scale != nullptr) ? ReadVec3(scale) : glm::vec3(1.0f, 1.0f, 1.0f);

                glm::mat4 matrix = glm::mat4();

                glm::mat4 matTransform = glm::mat4();
                matTransform = glm::translate(matTransform, vecPosition);

                glm::mat4 matRotation = glm::mat4();
                
                if(rotationAngle != NULL && strlen(rotationAngle) > 0)
                {
                    float rotationAngleF = std::stof(rotationAngle);
                    matRotation = glm::rotate(matRotation, rotationAngleF, vecRotationAxis);
                }
   
                glm::mat4 matScale = glm::mat4();
                matScale = glm::scale(matScale, vecScale);
                
                matrix = matScale * matRotation * matTransform;

				Mesh::Instance* instance = new Mesh::Instance(matrix);
				World::DatabaseEntity<Mesh::Instance>* dbInstance = new World::DatabaseEntity<Mesh::Instance>(instanceId, instance);
                model->AddInstance(dbInstance);
            }

			DatabaseEntity<Model>* modelDbEntity = new DatabaseEntity<Model>(modelId, model);
            level->AddModel(modelDbEntity);
        }

		sqlite3pp::query lightQuery(*db, SELECT_LEVEL_LIGHTS_QUERY);
		lightQuery.bind(":levelId", levelId);

		for (auto lightIter = lightQuery.begin(); lightIter != lightQuery.end(); ++lightIter)
		{
			int lightId;
			const char *lightType, *position, *ambient, *diffuse, *specular;
			double linearAtten, quadAtten;

			std::tie(lightId, lightType, position, ambient, diffuse, specular, linearAtten, quadAtten) =
				(*lightIter).get_columns<int, const char*, const char*, const char*, const char*, const char*, double, double>(0, 1, 2, 3, 4, 5, 6, 7);

			if (strcmp(lightType, "PointLight") == 0)
			{
				PointLight* pointLight = new PointLight(ReadVec3(position), ReadVec3(ambient), ReadVec3(diffuse), ReadVec3(specular), linearAtten, quadAtten);
				DatabaseEntity<PointLight>* lightEntity = new DatabaseEntity<PointLight>(lightId, pointLight);
				level->AddLight(lightEntity);
			}

		}

		return level;
    }


    return nullptr;
}

int GibEngine::World::Database::GetLastAutoincrementId()
{
    sqlite3pp::query qry(*db, SELECT_LAST_AUTOINCREMENT_ID);

    sqlite3pp::query::iterator iter = qry.begin();
    int id = (*iter).get<int>(0);
    
    return id;
}

int GibEngine::World::Database::SetLevelSkybox(int levelId, int skyboxId)
{
    sqlite3pp::command insertCmd(*db, SET_LEVEL_SKYBOX_QUERY);
	std::string levelIdStr = std::to_string(levelId);
	std::string skyboxIdStr = std::to_string(skyboxId);
    insertCmd.bind(":skyboxId", skyboxIdStr.c_str(), sqlite3pp::nocopy);
    insertCmd.bind(":levelId", levelIdStr.c_str(), sqlite3pp::nocopy);
    int res = insertCmd.execute();

    if(res != SQLITE_OK)
    {
        const char* errorMessage = db->error_msg();
        Logger::Instance->error("Failed to attach Skybox to Level! SQLite Error: {}", errorMessage);
        return -1;
    }

    return GetLastAutoincrementId();
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