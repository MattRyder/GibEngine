#pragma once

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Entity.h"
#include "Texture.h"

namespace GibEngine
{
	// A single vertex of a model
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;
		/*
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
		float Determinant;
		*/
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

			for (int i = 0; i < material->Textures.size(); i++)
			{
				Textures[i] = material->Textures.at(i)->GetTextureId();
			}
		}
	} MaterialBuffer;

	class Mesh : public Entity
	{
		GLuint VAO, VBO, EBO, instanceVBO;
		GLuint materialUBO = -1, materialUBOIndex = -1;

		std::vector<glm::mat4> instanceMatrices;

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Material*> materials;

		const char* directory;

	public:
		Mesh(const char* directory, aiMesh *mesh, const aiScene* scene);

		void ProcessMesh(aiMesh *mesh, const aiScene* scene);

		void LoadMeshData();
		void LoadMaterial(GLuint shaderProgram);
		void Render(GLuint shaderProgram, GLuint instanceCount, float deltaTime);

		void UpdateInstances();
		void AddInstance(glm::mat4 modelMatrix);

		virtual void UpdateUBO() override;

		virtual void Update(double deltaTime) override;

        std::vector<GibEngine::Texture*> LoadMaterialTextures(aiMaterial * material, aiTextureType type, GibEngine::TextureType textureType);
	};
}