#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"

namespace GibEngine
{
	class Model : public Entity
	{
		void LoadModel(File *modelFile);

	protected:
		std::vector<Mesh*> meshes;
		File* modelFile;
		const char* assetName;

	public:
		Model();
		Model(const char* modelFilename);
		Model(Mesh* mesh);

		void ProcessNode(aiNode* node, const aiScene* scene);

		void UpdateInstances();
		void AddInstance(glm::mat4 modelMatrix);
		virtual void Update(double deltaTime) override;

		int GetID() const override;
		const char* GetName() const override;
		const char* GetAssetName() const;
		std::vector<Mesh*> GetMeshes();
		std::vector<glm::mat4> GetModelInstances() const;
	};
}