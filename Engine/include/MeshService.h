#pragma once

#include "scene/Node.h"

namespace GibEngine
{
	class MeshService
	{
		static void ProcessNode(File* rootMeshFile, Scene::Node* parentNode, const aiScene* scene, aiNode* node);
		static Material* LoadMaterial(const char* meshDirectory, const aiMaterial* assimpMaterial);

		static std::vector<GibEngine::Texture*> LoadMaterialTextures(
			const char* meshDirectory, const aiMaterial* material,
			aiTextureType type, GibEngine::TextureType textureType);

	public:
		static Scene::Node* Load(File* file);
		static Scene::Node* GeneratePlane(unsigned int length, unsigned int width, int intervalSize);
	};
}