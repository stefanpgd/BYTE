#pragma once
#include <string>
#include <glm/glm.hpp>
#include "../Engine/Transform.h"

class Texture;
class ShaderProgram;
class Model;
class Camera;

class TextRenderer
{
public:
	TextRenderer(const std::string& fontName, Transform* transform);

	void Draw(Camera* camera);

private:
	unsigned int GetFontPosition(char c);

	Texture* font;
	ShaderProgram* textPipeline;
	Model* quad;

	Transform* transform;
};