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
#include "world/DatabaseEntity.h"

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
	public:
		static const int MOVE_SPEED = 10;

		class Instance
		{
			glm::mat4 matrix;

		public:
			Instance(glm::mat4 matrix) : matrix(matrix) { }
			Instance() : Instance(glm::mat4()) { }

			glm::mat4 GetMatrix() { return matrix; }

			glm::vec3 GetPosition()
			{ 
				return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
			}

			glm::vec3 GetScale()
			{
				return glm::vec3(matrix[0][0], matrix[1][1], matrix[2][2]);
			}

			void SetMatrix(glm::mat4 matrix)
			{
				this->matrix = matrix;
			}
		};

		enum Flags
		{
			RENDER_ENABLED = 1 << 0,
			RENDER_WIREFRAME = 1 << 1,
			RENDER_ARRAYS = 1 << 2,
		};

		Mesh();
		~Mesh();
		Mesh(const char *directory, aiMesh *mesh, const aiScene *scene);
		Mesh(std::vector<Vertex> vertices);

		void AddInstance(World::DatabaseEntity<Instance>* meshInstance);
		void UpdateInstance(unsigned int index, World::DatabaseEntity<Instance>* meshInstance);
		void DeleteInstance(World::DatabaseEntity<Mesh::Instance>* meshInstance);

		std::vector<World::DatabaseEntity<Instance>*> GetInstanceMatrices() const;
		std::vector<unsigned int> GetIndices() const;
		std::vector<Material*> GetMaterials() const;
		MeshUploadTicket* GetMeshUploadTicket() const;
		Flags GetFlags() const;
		std::vector<Vertex> GetVertices() const;

		bool IsInstanceMatricesDirty() const;
		bool IsUploaded();
		std::vector<GibEngine::Texture*> LoadMaterialTextures(aiMaterial *material, aiTextureType type, GibEngine::TextureType textureType);

		void ProcessMesh(aiMesh *mesh, const aiScene *scene);

		void SetIndices(std::vector<unsigned int> indices);
		void SetVertices(std::vector<Vertex> vertices);
		void SetInstanceMatricesDirty(bool isDirty);
		void SetMeshUploadTicket(MeshUploadTicket *meshUploadReciept);
		void SetFlags(Flags flags);

		virtual void Update(double deltaTime) override;

	private:
		MeshUploadTicket* uploadTicket = nullptr;
		Flags flags = Flags::RENDER_ENABLED;

		std::vector<World::DatabaseEntity<Instance>*> instanceMatrices;

		// Flags that the instance matrices must be updated on the GFX server
		bool instanceMatricesDirty;

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Material*> materials;

		glm::vec3 movementDir;

		const char* directory;
	};
}