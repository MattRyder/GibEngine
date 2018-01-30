#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sqlite3pp/sqlite3pp.h"

#include "DatabaseQuery.h"
#include "Skybox.h"
#include "PointLight.h"
#include "Logger.h"

#include "scene/Node.h"
#include "MeshService.h"

namespace GibEngine
{
    namespace World
    {
        class Database
        {
			// If Debug Mode, load with visibility meshes etc.
			bool debugMode;

            sqlite3pp::database* db;
            
			std::string ConvertVec3ToString(glm::vec3 vec);
            glm::vec3 ReadVec3(const char* vec3String);
            int GetLastAutoincrementId();

			Scene::Node* FindNode(int nodeId);

			bool SaveSceneNode(int parentNodeId, Scene::Node* node);
			bool SaveSceneNodeRecord(int parentId, Scene::Node* node);
			bool SaveEntity(Scene::Node* entityNode);

        public:
			Database(const char* databaseFilepath);
            Database(const char* databaseFilepath, bool debugMode);
			~Database();

			void Disconnect();
            
			bool CreateLevel(int nodeId, const char* name);

			Skybox* LoadSkybox(int skyboxId);
			PointLight* LoadLight(int lightId);
			Scene::Node* LoadMesh(int meshId);
			Scene::Node* LoadLevel(int rootNodeId);

            bool SaveSkybox(Scene::Node* skyboxSceneNode);
			bool SaveMesh(Scene::Node* meshNode);
			bool SavePointLight(Scene::Node* lightSceneNode);
			bool SaveLevel(Scene::Node* sceneRootNode);
        };
    }
}