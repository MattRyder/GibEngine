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
		std::vector<Mesh *> meshes;
		std::vector<glm::mat4> modelInstanceMatrices;
		File* modelFile;

	public:
		Model();
		Model(const char *modelFilename);
		~Model() override;

		void ProcessNode(aiNode *node, const aiScene *scene);

		void Render(GLuint shaderProgram, float deltaTime);
		void UpdateInstances();
		void AddInstance(glm::mat4 modelMatrix);
		virtual void Update(double deltaTime) override;

		int GetID() const override;
		std::string& GetName() const override;
		virtual void UpdateUBO() override;
	};
}