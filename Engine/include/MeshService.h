#pragma once

#include "scene/Node.h"

namespace GibEngine
{
	class MeshService
	{
		static void ProcessNode(File* rootMeshFile, Scene::Node* parentNode, const aiScene* scene, Mesh::Flags flags, aiNode* node);
		static Material* LoadMaterial(const char* meshDirectory, const aiMaterial* assimpMaterial);

		static Mesh::Flags ParseFlagsJson(const std::vector<json11::Json>& renderFlagsJsonArray);

		static std::vector<GibEngine::Texture*> LoadMaterialTextures(
			const char* meshDirectory, const aiMaterial* material,
			aiTextureType type, GibEngine::TextureType textureType);

		static Scene::Node* GeneratePlane(unsigned int length, unsigned int width, int intervalSize, Mesh::Flags flags);

	public:
		static Scene::Node* Load(File* file, json11::Json* generationData);
		static Scene::Node* Generate(json11::Json* generationData);

	};
}