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
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
		float Determinant = 0;
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
		GLuint Textures[static_cast<int>(TextureType::TEXTURETYPE_LAST)];

		material_uniform_block_t(const Material *material)
		{
			for (unsigned int i = 0; i < 3; i++)
			{
				AmbientColor[i] = material->AmbientColor[i];
				DiffuseColor[i] = material->DiffuseColor[i];
				SpecularColor[i] = material->SpecularColor[i];
			}

			Opacity = material->Opacity;
			Shininess = material->Shininess;

			for (unsigned int i = 0; i < material->Textures.size(); i++)
			{
				Textures[i] = material->Textures.at(i)->GetTextureId();
			}
		}
	} MaterialBuffer;

	// An object containing information regarding how to reference
	// the Mesh via the graphics server
	struct MeshUploadTicket
	{
		unsigned int vertexArrayObject;
		unsigned int totalVertices;
		unsigned int totalIndices;

		std::vector<unsigned int> buffers;
	};

	class Mesh : public Entity
	{
		MeshUploadTicket* uploadTicket = nullptr;

		std::vector<glm::mat4> instanceMatrices;

		// Flags that the instance matrices must be updated on the GFX server
		bool instanceMatricesDirty;

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Material*> materials;

		glm::vec3 movementDir;

		const char* directory;

	public:
		static const int MOVE_SPEED = 10;

		Mesh();
		Mesh(const char *directory, aiMesh *mesh, const aiScene *scene);
		Mesh(std::vector<Vertex> vertices);

		void AddInstance(glm::mat4 modelMatrix);
		void SetInstance(unsigned int index, glm::mat4 modelMatrix);

		std::vector<glm::mat4> GetInstanceMatrices() const;
		std::vector<unsigned int> GetIndices() const;
		std::vector<Material*> GetMaterials() const;
		MeshUploadTicket* GetMeshUploadTicket() const;
		std::vector<Vertex> GetVertices() const;

		bool IsInstanceMatricesDirty() const;
		bool IsUploaded();
		std::vector<GibEngine::Texture*> LoadMaterialTextures(aiMaterial *material, aiTextureType type, GibEngine::TextureType textureType);

		void ProcessMesh(aiMesh *mesh, const aiScene *scene);

		void SetIndices(std::vector<unsigned int> indices);
		void SetVertices(std::vector<Vertex> vertices);
		void SetInstanceMatricesDirty(bool isDirty);
		void SetMeshUploadTicket(MeshUploadTicket *meshUploadReciept);

		virtual void Update(double deltaTime) override;
	};
}