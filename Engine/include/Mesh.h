#pragma once

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <json11.hpp>

#include "EnumFlags.h"
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

		enum class Flags : int
		{
			RENDER_ENABLED = 1 << 1,
			RENDER_WIREFRAME = 1 << 2,
			RENDER_ARRAYS = 1 << 3,
			RENDER_DEFERRED = 1 << 4,
			RENDER_FORWARD = 1 << 5
		};

		Mesh(const char* name);
		Mesh(const char* name, const char* ownerFileName, std::vector<Vertex> vertices);
		Mesh(const char* name, const char* ownerAssetName, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Material*> material);
		~Mesh();

		Flags GetFlags() const;
		std::vector<unsigned int> GetIndices() const;
		std::vector<Material*> GetMaterials() const;
		MeshUploadTicket* GetMeshUploadTicket() const;
		std::vector<Vertex> GetVertices() const;
		const char* GetOwnerAssetName() const;
		const json11::Json* GetGenerationData() const;

		bool IsUploaded();
		std::vector<GibEngine::Texture*> LoadMaterialTextures(aiMaterial *material, aiTextureType type, GibEngine::TextureType textureType);

		void ProcessMesh(aiMesh *mesh, const aiScene *scene);

		void SetIndices(std::vector<unsigned int> indices);
		void SetVertices(std::vector<Vertex> vertices);
		void SetMeshUploadTicket(MeshUploadTicket *meshUploadReciept);
		void SetFlags(Flags flags);
		void SetGenerationData(json11::Json* generationData);

		virtual void Update(double deltaTime) override;
 
		static bool FlagMask(Flags x) { return static_cast<char>(x) != 0; };

	private:
		json11::Json* generationData = nullptr;
		MeshUploadTicket* uploadTicket = nullptr;
		Flags flags = Flags::RENDER_ENABLED;

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Material*> materials;

		const char* ownerAssetName;
	};

	GIB_FLAGS(Mesh::Flags)
}