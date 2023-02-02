#pragma once
#include <string>
#include <glm/glm.hpp>
#include "../Engine/Transform.h"

class Texture;
class ShaderProgram;
class Model;

class UIRenderer
{
public: 
	UIRenderer(const std::string& fileName);

	void ImGuiDraw();

	// Position is using NDC values 
	// With a 1920x1080 screen, -1,-1 would be top left, 1,1 would be bottom right
	// Using this we can easily change viewport size 
	glm::vec2 Position = glm::vec2(0.0f, 0.0f);

	// Size is based on the default image size supplied by the texture 
	// a 300x300 image with scale 1.0,1.0 would be 300x300 on the screen. 
	glm::vec2 Size = glm::vec2(1.0f, 1.0f);

	bool isActive = true;

private:
	void Draw();

	std::string fileName;

	Texture* texture;
	ShaderProgram* shaderProgram;
	Model* quad;
	
	float screenWRep;
	float screenHRep;

	Transform transform;

	friend class UISystem;
};