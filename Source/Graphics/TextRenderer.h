#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Engine/Transform.h"

class Texture;
class ShaderProgram;
class Model;
class Camera;

class TextRenderer
{
public:
	TextRenderer(const std::string& text, Transform* transform);

	void Draw(Camera* camera);
	void UpdateText(const std::string& text);

	glm::vec4 color;
	float emission;

private:
	unsigned int GetFontPosition(char c);

	float letterOffset = 1.0f;
	std::string text;

	Texture* font;
	ShaderProgram* textPipeline;
	Model* quad;

	Transform* transform;
	Transform letterTransform;
};