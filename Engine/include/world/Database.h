#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sqlite3pp/sqlite3pp.h"

#include "DatabaseQuery.h"
#include "DatabaseEntity.h"
#include "Level.h"
#include "Logger.h"

#include "scene/Node.h"
#include "MeshService.h"

namespace GibEngine
{
    namespace World
    {
        class Database
        {
            sqlite3pp::database* db;
            
			std::string ConvertVec3ToString(glm::vec3 vec);
            glm::vec3 ReadVec3(const char* vec3String);
            int GetLastAutoincrementId();

			Scene::Node* FindNode(int nodeId);

			bool SaveSceneNode(int parentNodeId, Scene::Node* node);
			bool SaveSceneNodeRecord(int parentId, Scene::Node* node);

        public:
            Database(const char* databaseFilepath);
			~Database();

			void Disconnect();
            
			bool CreateLevel(int nodeId, const char* name);

			Scene::Node* LoadSkybox(int skyboxId);
			Scene::Node* LoadLight(int lightId);
			Scene::Node* LoadMesh(int meshId);
			Scene::Node* LoadLevel(int rootNodeId);

            bool SaveSkybox(Scene::Node* skyboxSceneNode);
			bool SaveMesh(Scene::Node* meshNode);
			bool SavePointLight(Scene::Node* lightSceneNode);
			bool SaveLevel(Scene::Node* sceneRootNode);
			
        };
    }
}