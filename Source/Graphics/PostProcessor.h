#pragma once
#include <glm/glm.hpp>

class Framebuffer;
class ShaderProgram;
class ScreenQuad;

class PostProcessor
{
public:
	PostProcessor(unsigned int windowWidth, unsigned int windowHeight);

	void PostProcess(Framebuffer* sceneBuffer);
	void DebugDrawImGui();

private:
	void ApplyBloom(Framebuffer* sceneBuffer);

	void SetupBloom(unsigned int windowWidth, unsigned int windowHeight);

	// Screen, HDR, Exposure //
	ScreenQuad* screenQuad;
	ShaderProgram* screenShader;
	float exposure = 1.0f;

	// Bloom //
	ShaderProgram* gaussianBlurShader;
	unsigned int bloomFBO[2];
	unsigned int bloomColorBuffer[2];
	unsigned int bloomBufferIndex = 0;

	// Chromatic Aberration // 
	glm::vec2 redOffset;
	glm::vec2 greenOffset;
	glm::vec2 blueOffset;
};