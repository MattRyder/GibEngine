#include "world/Database.h"
#include <iostream>

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

    int skyboxId = SaveSkybox(level->GetSkybox());
    if(skyboxId == -1)
    {
        Logger::Instance->error("Failed to set Level Skybox! {}", level->GetSkybox()->GetName());
        return false;
    }
    SetLevelSkybox(levelId, skyboxId);

    for(auto model : level->GetModels())
    {
        int modelId = SaveModel(levelId, model);
        if(modelId == -1)
        {
            Logger::Instance->error("Failed to create WorldDb Model! {}", model->GetAssetName());
            return false;
        }

        for(auto modelMatrix : model->GetModelInstances())
        {
            glm::vec3 pos = glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
            glm::vec3 scale = glm::vec3(modelMatrix[0][0], modelMatrix[1][1], modelMatrix[2][2]);
            int instanceId = SaveInstance(modelId, pos, glm::vec3(), 0.0f, scale);
            if(modelId == -1)
            {
                Logger::Instance->error("Failed to create WorldDb Model Instance: {}", model->GetAssetName());
                return false;
            }
        }
    }

    return true;
}

int GibEngine::World::Database::SaveModel(int levelId, Model* model)
{
    sqlite3pp::command insertCmd(*db, CREATE_MODEL_QUERY);
    insertCmd.bind(":levelId", std::to_string(levelId).c_str(), sqlite3pp::nocopy);
    insertCmd.bind(":assetName", model->GetAssetName(), sqlite3pp::nocopy);
    int res = insertCmd.execute();

    if(res != SQLITE_OK)
    {
        const char* errorMessage = db->error_msg();
        Logger::Instance->error("Failed to create WorldDb Model! SQLite Error: {}", errorMessage);
        return -1;
    }

    return GetLastAutoincrementId();
}

int GibEngine::World::Database::SaveSkybox(Skybox* skybox)
{
    sqlite3pp::command insertCmd(*db, CREATE_SKYBOX_QUERY);
    insertCmd.bind(":assetName", skybox->GetName(), sqlite3pp::nocopy);
    insertCmd.bind(":extension", skybox->GetExtension(), sqlite3pp::nocopy);
    int res = insertCmd.execute();

    if(res != SQLITE_OK)
    {
        const char* errorMessage = db->error_msg();
        Logger::Instance->error("Failed to create WorldDb Skybox! SQLite Error: {}", errorMessage);
        return -1;
    }

    return GetLastAutoincrementId();
}


int GibEngine::World::Database::SaveInstance(int modelId, glm::vec3 position, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 scale)
{
    sqlite3pp::command insertCmd(*db, CREATE_INSTANCE_QUERY);
    insertCmd.bind(":modelId", std::to_string(modelId).c_str(), sqlite3pp::nocopy);

    const char *rotationAn = std::to_string(rotationAngle).c_str();
    insertCmd.bind(":rotationAngle", rotationAn, sqlite3pp::nocopy);
    
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
        Logger::Instance->error("Failed to create WorldDb Model! SQLite Error: {}", errorMessage);
        return -1;
    }

    return GetLastAutoincrementId();
}

GibEngine::World::Level* GibEngine::World::Database::FindLevel(int id)
{
    int levelId;
    const char* levelName, *skyboxName, *skyboxExt;

    sqlite3pp::query qry(*db, SELECT_LEVEL_QUERY);
    qry.bind(1, id);
    sqlite3pp::query::iterator iter = qry.begin();
    
    std::tie(levelId, levelName, skyboxName, skyboxExt) =
        (*iter).get_columns<int, const char*, const char*, const char*>(0, 1, 2, 3);

    if(levelId > 0)
    {
        Level* level = new Level(levelId, strdup(levelName));

        if(skyboxName != nullptr && skyboxExt != nullptr)
        {
            Skybox* skybox = new Skybox(skyboxName, skyboxExt);
            level->SetSkybox(skybox);
        }        
        
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
                const char* position;
                const char* rotationAxis;
                const char* rotationAngle;
                const char* scale;

                std::tie(position, rotationAxis, rotationAngle, scale) =
                (*iIter).get_columns<const char*, const char*, const char*, const char*>(0, 1, 2, 3);   

                glm::vec3 vecPosition = (position != nullptr) ? ReadVec3(position) : glm::vec3();
                glm::vec3 vecRotationAxis = (rotationAxis != nullptr) ? ReadVec3(rotationAxis) : glm::vec3();
                glm::vec3 vecScale = (scale != nullptr) ? ReadVec3(scale) : glm::vec3(1.0f, 1.0f, 1.0f);

                glm::mat4 matrix = glm::mat4();

                glm::mat4 matTransform = glm::mat4();
                matTransform = glm::translate(matTransform, vecPosition);

                glm::mat4 matRotation = glm::mat4();
                
                if(rotationAngle != NULL)
                {
                    float rotationAngleF = std::stof(rotationAngle);
                    matRotation = glm::rotate(matRotation, rotationAngleF, vecRotationAxis);
                }
   
                glm::mat4 matScale = glm::mat4();
                matScale = glm::scale(matScale, vecScale);
                
                matrix = matScale * matRotation * matTransform;

                model->AddInstance(matrix);
            }

            level->AddModel(model);
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

bool GibEngine::World::Database::SetLevelSkybox(int levelId, int skyboxId)
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

glm::vec3 GibEngine::World::Database::ReadVec3(const char* vec3String)
{
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