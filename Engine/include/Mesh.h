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
		float Determinant;
	};

	struct MaterialTexture
	{
		std::shared_ptr<Texture> texture;
		std::string textureUniformName;
	};

	// The color and shine of the Model
	struct Material
	{
		glm::vec3 AmbientColor;
		glm::vec3 DiffuseColor;
		glm::vec3 SpecularColor;
		float Opacity;
		unsigned int Shininess;
		std::vector<MaterialTexture> Textures;
	};

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
		enum class Flags : char
		{
			RENDER_ENABLED = 1 << 1,
			RENDER_WIREFRAME = 1 << 2,
			RENDER_ARRAYS = 1 << 3,
			RENDER_DEFERRED = 1 << 4,
			RENDER_FORWARD = 1 << 5
		};

		Mesh(std::string name, std::shared_ptr<MeshUploadTicket> uploadTicket, std::shared_ptr<Material> material);

		Flags GetFlags() const;
		std::shared_ptr<Material> GetMaterial() const;
		std::shared_ptr<MeshUploadTicket> GetMeshUploadTicket() const;
		const json11::Json& GetGenerationData() const;

		bool IsUploaded();

		void SetFlags(Flags flags);
		void SetGenerationData(json11::Json generationData);

		virtual void Update(double deltaTime) override;
 
		static bool FlagMask(Flags x) { return static_cast<char>(x) != 0; };

	private:
		json11::Json generationData;
		Flags flags;

		std::shared_ptr<MeshUploadTicket> uploadTicket;
		std::shared_ptr<Material> material;
	};

	inline bool operator<(const Mesh& lhs, const Mesh& rhs) { return lhs.GetID() < rhs.GetID(); }

	GIB_FLAGS(Mesh::Flags)
}