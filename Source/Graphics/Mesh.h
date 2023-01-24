#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

class ShaderProgram;
class Texture;

struct aiMesh;
struct aiScene;
struct aiMaterial;

struct VertexData
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoord;
	glm::vec3 Tangent;
};

class Mesh
{
public:
	Mesh(aiMesh* mesh, const aiScene* scene);

	void Draw();

private:
	void SetupBuffers();

	unsigned int indicesCount = 0;
	unsigned int VBO, VAO, EBO;

	std::vector<VertexData> vertexData;
	std::vector<unsigned int> indexData;
};