#pragma once
#include <vector>
#include <string>

class ShaderProgram;
class Mesh;
class Transform;
class Camera;

// Assimp //
struct aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;
enum aiTextureType;

class Model;

class Model
{
public:
	Model(const std::string& filePath, Transform* transform);

	void Draw(ShaderProgram* shaderProgram);
	void Draw(ShaderProgram* shaderProgram, Camera* camera);

	std::string& GetFilePath();

private:
	void ProcessNode(aiNode* node, const aiScene* scene);

	Transform* transform;
	std::string filePath;
	std::vector<Mesh*> meshes;
};

static std::vector<Model*> ModelArchive;