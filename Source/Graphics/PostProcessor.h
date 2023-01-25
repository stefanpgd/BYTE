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

	// Chromatic Aberration // 
	static inline bool chromaticAberrationFromCenter = true;
	static inline float chromaticAberrationCenterStrength = 0.0f;
	static inline glm::vec2 redOffset = glm::vec2(0.01, -0.01);
	static inline glm::vec2 greenOffset;
	static inline glm::vec2 blueOffset = glm::vec2(-0.01, 0.01);

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
};