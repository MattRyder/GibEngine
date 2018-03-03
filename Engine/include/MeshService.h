#pragma once

#include <thread>

#ifdef WIN32
#include "filesystem/WindowsFileSystem.h"
#elif __unix__
#include "filesystem/UnixFileSystem.h"
#endif

#include "renderer/api/IGraphicsApi.h"
#include "scene/Node.h"
#include "PointLight.h"

namespace GibEngine
{
	class MeshService
	{
		const static size_t CUBE_VERTEX_DATA_SIZE = 108;
		const static float CUBE_VERTEX_DATA[CUBE_VERTEX_DATA_SIZE];

		static void ProcessNode(const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, Scene::Node* parentNode, const std::string& meshFilePath, const aiScene& scene, Mesh::Flags flags, aiNode& node);
		
		static std::shared_ptr<Material> LoadMaterial(const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, const aiMaterial& assimpMaterial, const std::string& materialTextureDirectoryPath);

		static Mesh::Flags ParseFlagsJson(const std::vector<json11::Json> renderFlagsJsonArray);

		static std::vector<Vertex> GeneratePlane(unsigned int length, unsigned int width, int intervalSize);

	public:
		static const json11::Json CUBE_GENERATION_JSON;

		static Scene::Node* Load(const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, const std::string meshFileRelativePath, const json11::Json generationData);
		static Mesh* Generate(const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, const json11::Json generationData);

		static std::shared_ptr<Texture> LoadCubemap(const std::shared_ptr<Renderer::API::IGraphicsApi>& graphicsApi, const std::string& skyboxAbsolutePathWithName, const std::string& extension);
	};
}