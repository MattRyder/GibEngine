#pragma once

#include <vector>
#include "Model.h"
#include "Skybox.h"
#include "DatabaseEntity.h"

namespace GibEngine
{
    namespace World
    {
        class Level : DatabaseEntity
        {
            const char* name;
            Skybox* skybox;

            std::vector<GibEngine::Model*>* models;

        public:
            Level(int id, const char* name);

            int GetId();
            const char* GetName();

            void AddModel(GibEngine::Model* model);
            void SetSkybox(GibEngine::Skybox* skybox);

            std::vector<GibEngine::Model*> GetModels();
            GibEngine::Skybox* GetSkybox();
        };
    }
}