#pragma once

#include <vector>
#include "Model.h"
#include "Skybox.h"
#include "DatabaseEntity.h"

namespace GibEngine
{
    namespace World
    {
        class Level : public DatabaseEntity<Level>
        {
            const char* name;
            DatabaseEntity<Skybox>* skybox;
            std::vector<DatabaseEntity<Model>*> modelEntities;

        public:
            Level(int id, const char* name);
			~Level();

            int GetId();
            const char* GetName();

            void AddModel(DatabaseEntity<GibEngine::Model>* model);
            void SetSkybox(DatabaseEntity<GibEngine::Skybox>* skybox);

			/*
				Adds a model via it's asset name, a quicker version of adding via DatabaseEntity
			 */
			DatabaseEntity<Model>* AddModel(const char* modelFilename);

			std::vector<Model*> GetModels();
			std::vector<DatabaseEntity<Model>*> GetModelEntities();
            GibEngine::Skybox* GetSkybox();
			DatabaseEntity<Skybox>* GetSkyboxEntity();
        };
    }
}