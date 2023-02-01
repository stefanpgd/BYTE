#pragma once
#include <string>
#include <glm/glm.hpp>

class Texture;
class ShaderProgram;
class Model;

class UIRenderer
{
public: 
	UIRenderer(const std::string& fileName);

	void Update(float deltaTime);
	void Draw();

	glm::vec2 Position;
	glm::vec2 Size; 

private:
	Texture* texture;
	ShaderProgram* shaderProgram;
	Model* quad;
};