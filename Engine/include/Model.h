#pragma once

#include <vector>

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Entity.h"
#include "Texture.h"

namespace GibEngine
{
    class Model : Entity
    {
        // A single vertex of a model
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec3 Normal;
            glm::vec2 TexCoord;
            glm::vec3 Tangent;
            glm::vec3 Bitangent;
            float Determinant;
        };

        // The color and shine of the Model
        typedef struct material_t
        {
            glm::vec3 AmbientColor;
            glm::vec3 DiffuseColor;
            glm::vec3 SpecularColor;
            GLfloat Opacity;
            GLuint Shininess;
            std::vector<Texture*> Textures;
        } Material;

        typedef struct material_uniform_block_t
        {
            GLfloat AmbientColor[3];
            GLfloat DiffuseColor[3];
            GLfloat SpecularColor[3];
            GLfloat Opacity;
            GLuint Shininess;
            GLuint Textures[static_cast<int>(TextureType::NORMAL)];

            material_uniform_block_t(const Material *material)
            {
                for (int i = 0; i < 3; i++)
                {
                    AmbientColor[i] = material->AmbientColor[i];
                    DiffuseColor[i] = material->DiffuseColor[i];
                    SpecularColor[i] = material->SpecularColor[i];
                }

                Opacity = material->Opacity;
                Shininess = material->Shininess;

                for (int i = 0; i < static_cast<int>(TextureType::NORMAL); i++)
                {
                    Textures[i] = material->Textures.at(i)->GetTextureId();
                }
            }
        } MaterialBuffer;

        void LoadModel(File *modelFile);
        void LoadMaterialUBO(Material *material);

    protected:
        GLuint VAO, VBO, EBO, modelMatrixLocation = 0;
        GLuint materialUBO = -1, materialUBOIndex = -1;

        glm::mat4 modelMatrix;
        File* modelFile;

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Material*> materials;

    public:
        Model();
        Model(const char *modelFilename);
        ~Model() override;

        void ProcessNode(aiNode *node, const aiScene *scene);
        void ProcessMesh(aiMesh *mesh, const aiScene *scene);

        void LoadModelData();
        std::vector<GibEngine::Texture*> LoadMaterialTextures(aiMaterial * material, aiTextureType type, GibEngine::TextureType textureType);

        virtual void Render(){}
        void Render(GLuint shaderProgram, float deltaTime);
        void Update(double deltaTime) override;

        int GetID() const override;
        glm::vec3& GetPosition() const override;
        std::string& GetName() const override;
    };
}