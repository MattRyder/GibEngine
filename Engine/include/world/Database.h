#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "sqlite3pp/sqlite3pp.h"

#include "DatabaseQuery.h"
#include "Level.h"
#include "Logger.h"

namespace GibEngine
{
    namespace World
    {
        class Database
        {
            sqlite3pp::database* db;
            
            glm::vec3 ReadVec3(const char* vec3String);
            int GetLastAutoincrementId();
            bool SetLevelSkybox(int levelId, int skyboxId);

        public:
            Database(const char* databaseFilepath);
			~Database();

			void Disconnect();
            
            Level* CreateLevel(const char* levelName);

            bool SaveLevel(Level* level);
            int SaveSkybox(Skybox* skybox);
            int SaveModel(int levelId, Model* model);
            int SaveInstance(int modelId,
                glm::vec3 position, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 scale);  

            Level* FindLevel(int id);
        };
    }
}