#include "..\include\Mesh.h"

GibEngine::Mesh::Mesh(const char* directory, aiMesh *mesh, const aiScene* scene) : Entity(EntityType::MODEL)
{
	this->directory = directory;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &instanceVBO);

	glGenBuffers(1, &uniformBufferObject);
	glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferObject);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(float) * 36, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	ProcessMesh(mesh, scene);
	this->LoadMeshData();
}

void GibEngine::Mesh::ProcessMesh(aiMesh *mesh, const aiScene* scene)
{
	//VerticesCount += mesh->mNumVertices;
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		if (mesh->HasTangentsAndBitangents())
		{
			const aiVector3D* tangent = &(mesh->mTangents[i]);
			const aiVector3D* bitangent = &(mesh->mBitangents[i]);
			const aiVector3D* normal = &(mesh->mNormals[i]);

			//vertex.Tangent = glm::vec3(tangent->x, tangent->y, tangent->z);
			//vertex.Bitangent = glm::vec3(bitangent->x, bitangent->y, bitangent->z);
			vertex.Normal = glm::vec3(normal->x, normal->y, normal->z);
			//float det = dot(cross(vertex.Normal, vertex.Tangent), vertex.Bitangent);
			//vertex.Determinant = (det < 0.0f) ? -1.0f : 1.0f;
		}

		vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			vertex.TexCoord = texCoord;
		}
		else
		{
			vertex.TexCoord = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	//load materials:
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	Material *mat = new Material();

	aiColor3D amb, diff, spec;
	float opacity;
	int shine;

	material->Get(AI_MATKEY_COLOR_SPECULAR, spec);
	material->Get(AI_MATKEY_COLOR_DIFFUSE, diff);
	material->Get(AI_MATKEY_COLOR_AMBIENT, amb);
	material->Get(AI_MATKEY_SHININESS, shine);
	material->Get(AI_MATKEY_OPACITY, opacity);

	mat->AmbientColor = glm::vec3(amb.r, amb.g, amb.b);
	mat->DiffuseColor = glm::vec3(diff.r, diff.g, diff.b);
	mat->SpecularColor = glm::vec3(spec.r, spec.g, spec.b);
	mat->Opacity = opacity;
	mat->Shininess = shine;

	std::vector<Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
	mat->Textures.insert(mat->Textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	std::vector<Texture*> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
	mat->Textures.insert(mat->Textures.end(), specularMaps.begin(), specularMaps.end());
	std::vector<Texture*> heightMaps = LoadMaterialTextures(material, aiTextureType_UNKNOWN, TextureType::HEIGHT);
	mat->Textures.insert(mat->Textures.end(), heightMaps.begin(), heightMaps.end());
	std::vector<Texture*> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::NORMAL);
	mat->Textures.insert(mat->Textures.end(), normalMaps.begin(), normalMaps.end());

	this->materials.push_back(mat);
}

void GibEngine::Mesh::LoadMeshData()
{
	size_t vboSize = vertices.size() * sizeof(Vertex);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vboSize, &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// Setup Position:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// Setup Normals:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	// Setup TexCoord:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));

	//// Setup Normals:
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));

	//// Setup Normals:
	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}

void GibEngine::Mesh::LoadMaterial(GLuint shaderProgram) 
{
	for (int i = 0; i < 1; i++)
	{
		struct material_uniform_block_t material(materials[i]);
		
		for (unsigned int tIndex = 0; tIndex < materials[i]->Textures.size(); tIndex++)
		{
			const char *textureTypeStr = Texture::TextureTypeStrings[tIndex];

			glActiveTexture(GL_TEXTURE0 + i);

			std::string textureUniformName = std::string("texture_" + std::string(textureTypeStr) + "1");
			GLint textureLocation = glGetUniformLocation(shaderProgram, textureUniformName.c_str());
			glUniform1i(textureLocation, static_cast<GLfloat>(tIndex));
			glBindTexture(GL_TEXTURE_2D, material.Textures[tIndex]);
		}

		GLint surfaceAmbientLocation = glGetUniformLocation(shaderProgram, "material.ambient");
		if (surfaceAmbientLocation > 0) { glUniform3fv(surfaceAmbientLocation, 1, material.AmbientColor); }

		GLuint surfaceDiffuseLocation = glGetUniformLocation(shaderProgram, "material.diffuse");
		if (surfaceDiffuseLocation > 0) { glUniform3fv(surfaceDiffuseLocation, 1, material.DiffuseColor); }

		GLuint surfaceSpecularLocation = glGetUniformLocation(shaderProgram, "material.specular");
		if (surfaceAmbientLocation > 0) { glUniform3fv(surfaceSpecularLocation, 1, material.SpecularColor); }

		GLuint surfaceShininessLocation = glGetUniformLocation(shaderProgram, "material.shininess");
		if (surfaceShininessLocation > 0) { glUniform1f(surfaceShininessLocation, material.Shininess); }

		GLuint surfaceOpacityLocation = glGetUniformLocation(shaderProgram, "material.opacity");
		if (surfaceOpacityLocation > 0) { glUniform1f(surfaceOpacityLocation, material.Opacity); }
	}
}

void GibEngine::Mesh::Render(GLuint shaderProgram, GLuint instanceCount, float deltaTime)
{
	LoadMaterial(shaderProgram);

	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instanceCount);
}

void GibEngine::Mesh::UpdateInstances()
{
	const int vec4Size = sizeof(glm::vec4);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, instanceMatrices.size() * sizeof(glm::mat4), &instanceMatrices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)vec4Size);
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(vec4Size * 2));
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(vec4Size * 3));

	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);
}

void GibEngine::Mesh::AddInstance(glm::mat4 modelMatrix)
{
	this->instanceMatrices.push_back(modelMatrix);
	UpdateInstances();
}

void GibEngine::Mesh::UpdateUBO()
{
	const int vec4Size = sizeof(glm::vec4);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, instanceMatrices.size() * sizeof(glm::mat4), &instanceMatrices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)vec4Size);
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(vec4Size * 2));
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(vec4Size * 3));

	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);
}

void GibEngine::Mesh::Update(double deltaTime)
{
}

std::vector<GibEngine::Texture*> GibEngine::Mesh::LoadMaterialTextures(aiMaterial * material, aiTextureType type, GibEngine::TextureType textureType)
{
	std::vector<Texture *> textures;
	for (GLuint i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);

		std::string* texturePath = new std::string(this->directory);
		texturePath->append("/").append(str.C_Str());

		Texture* texture = new Texture(textureType, texturePath);
		textures.push_back(texture);
	}
	return textures;

}
