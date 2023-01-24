#pragma once
#include <vector>
#include <glm/glm.hpp>

class Framebuffer
{
public:
	Framebuffer(unsigned int windowWidth, unsigned int windowHeight, bool doDepthTest, int colorBufferAmount);

	void BindBuffer(glm::vec3 clearColor = glm::vec3(0.0));
	void BindTexture(unsigned int textureSlot = 0, unsigned int colorBufferIndex = 0);

private:
	bool depthTest = true;
	unsigned int FBO; // Frame Buffer Object
	std::vector<unsigned int> FCO; // Frame Color Objects
};