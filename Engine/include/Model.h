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
		~Model();

		void ProcessNode(aiNode* node, const aiScene* scene);

		virtual void Update(double deltaTime) override;

		void AddInstance(World::DatabaseEntity<Mesh::Instance>* modelMatrix);
		void UpdateInstance(unsigned int index, World::DatabaseEntity<Mesh::Instance>* modelMatrix);
		void DeleteInstance(World::DatabaseEntity<Mesh::Instance>* modelMatrix);

		int GetID() const override;
		const char* GetName() const override;
		const char* GetAssetName() const;
		std::vector<Mesh*> GetMeshes();
		std::vector<World::DatabaseEntity<Mesh::Instance>*> GetModelInstances() const;

		void SetWireframeMode(bool wireframeOn);
		void SetShouldRender(bool shouldRender);
	};
}