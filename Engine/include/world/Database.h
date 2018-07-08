#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sqlite3pp/sqlite3pp.h"

#include "DatabaseQuery.h"
#include "Skybox.h"
#include "PointLight.h"
#include "Logger.h"

#include "MeshService.h"
#include "filesystem/IFileSystem.h"

namespace GibEngine
{
    namespace World
    {
        class Database
        {
			// If Debug Mode, load with visibility meshes etc.
			bool debugMode;

            std::shared_ptr<sqlite3pp::database> db;
			std::shared_ptr<FileSystem::IFileSystem> fs;
			std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi;
            
			std::string ConvertVec3ToString(const glm::vec3& vec);
            glm::vec3 ReadVec3(std::string vec3String);
            int GetLastAutoincrementId();

			//Scene::Node* FindNode(int nodeId);

			//bool SaveSceneNode(int parentNodeId, Scene::Node* node);
			//bool SaveSceneNodeRecord(int parentId, Scene::Node* node);
			//bool SaveEntity(Scene::Node* entityNode);

        public:
			Database(const std::string& databaseFilepath, std::shared_ptr<FileSystem::IFileSystem> fs, std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi);
            Database(const std::string& databaseFilepath, std::shared_ptr<FileSystem::IFileSystem> fs, std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, bool debugMode);
			~Database();

			void Disconnect();
            
			bool CreateLevel(int nodeId, const std::string& name);

			Skybox* LoadSkybox(int skyboxId);
			PointLight* LoadLight(int lightId);
			//Scene::Node* LoadMesh(int meshId);
			//std::shared_ptr<BaseEntity> LoadLevel(int id);

   //         bool SaveSkybox(Scene::Node* skyboxSceneNode);
			//bool SaveMesh(Scene::Node* meshNode);
			//bool SavePointLight(Scene::Node* lightSceneNode);
			//bool SaveLevel(Scene::Node* sceneRootNode);
        };
    }
}