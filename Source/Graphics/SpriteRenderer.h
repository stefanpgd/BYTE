#pragma once
#include <string>

class Texture;
class ShaderProgram;
class Model;
class Camera;
class Transform;

class SpriteRenderer
{
public:
	SpriteRenderer(const std::string& fileName, Transform* transform, unsigned int framesInTexture = 1, float framesPerSecond = 8.0f);

	void Update(float deltaTime);
	void Draw(Camera* camera);

	void SetAnimationStride(unsigned int startFrame, unsigned int endFrame, float framesPerSecond);
	
	float FramesPerSecond;
	bool FlipX = false;
	bool FlipY = false;
	bool PauseAnimation = false;

private:
	Texture* texture;
	ShaderProgram* shaderProgram;
	Model* quad;

	// Animation //
	unsigned int framesInTexture = 0;
	unsigned int currentFrame = 0;

	bool hasAnimationStride = false;
	unsigned int animationStart = 0;
	unsigned int animationEnd = 0;
	float animationTimer = 0.0f;
};