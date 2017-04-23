#include "Model.h"

GibEngine::Model::Model() : Entity(EntityType::MODEL)
{
    this->modelMatrix = glm::mat4();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

GibEngine::Model::Model(const char* modelFilename) : Model()
{
    modelFile = File::GetModelFile(modelFilename);
    LoadModel(modelFile);
}

GibEngine::Model::~Model()
{
}

void GibEngine::Model::LoadModel(File *modelFile)
{
    Assimp::Importer importer;
    const char *modelFilePath = modelFile->GetPath();
    // printf("%s", modelFile->GetPath());
    const aiScene *scene = importer.ReadFile(modelFile->GetPath(),
                                aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Logger::Instance->error("Failed to find Model: {}", importer.GetErrorString());
        return;
    }

    ProcessNode(scene->mRootNode, scene);
    importer.FreeScene();

    this->LoadModelData();
    
    // Load Material UBO:
    this->LoadMaterialUBO(this->materials[0]);
}

void GibEngine::Model::LoadModelData()
{
    size_t vboSize = vertices.size() * sizeof(Vertex);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vboSize, &vertices[0], GL_STATIC_DRAW);

    // Setup Position:
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    // Setup Normals:
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

    // Setup TexCoord:
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));

    // Setup Normals:
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));

    // Setup Normals:
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
}

void GibEngine::Model::LoadMaterialUBO(Material *material)
{
    // Setup all Uniform Buffer Objects for the uniforms:
    materialUBO = 0;
    glGenBuffers(1, &materialUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, materialUBO);

    MaterialBuffer buffer = MaterialBuffer(material);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialBuffer), &buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GibEngine::Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    // Process all the node's meshes:
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }

    //Then process all the child nodes:
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

void GibEngine::Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    //VerticesCount += mesh->mNumVertices;
    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        if (mesh->HasTangentsAndBitangents()) {
            const aiVector3D* tangent = &(mesh->mTangents[i]);
            const aiVector3D* bitangent = &(mesh->mBitangents[i]);
            const aiVector3D* normal = &(mesh->mNormals[i]);

            vertex.Tangent = glm::vec3(tangent->x, tangent->y, tangent->z);
            vertex.Bitangent = glm::vec3(bitangent->x, bitangent->y, bitangent->z);
            vertex.Normal = glm::vec3(normal->x, normal->y, normal->z);
            float det = dot(cross(vertex.Normal, vertex.Tangent), vertex.Bitangent);
            vertex.Determinant = (det < 0.0f) ? -1.0f : 1.0f;
        }

        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0]) {
            glm::vec2 texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            vertex.TexCoord = texCoord;
        }
        else {
            vertex.TexCoord = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++) {
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

std::vector<GibEngine::Texture*> GibEngine::Model::LoadMaterialTextures(aiMaterial *material, aiTextureType type, GibEngine::TextureType textureType) {
    std::vector<Texture*> textures;
    for (GLuint i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);

        std::string pwd = modelFile->GetPath();
        std::string *texturePath = new std::string(std::string(modelFile->GetDirectory()) + "/" + std::string(str.C_Str()));
        Texture* texture = new Texture(textureType, texturePath);
        textures.push_back(texture);
    }
    return textures;
}

void GibEngine::Model::Render(GLuint shaderProgram, float deltaTime)
{
    if(this->modelMatrixLocation == 0)
        this->modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix");

    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLint>(indices.size()), GL_UNSIGNED_INT, nullptr);


}

void GibEngine::Model::Update(double deltaTime)
{
}

int GibEngine::Model::GetID() const
{
    return 0;
}

glm::vec3& GibEngine::Model::GetPosition() const
{
    return *Entity::entityPosition;
}

std::string& GibEngine::Model::GetName() const
{
    return *Entity::entityName;
}
