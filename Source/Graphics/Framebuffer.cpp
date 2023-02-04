#include "Graphics/Framebuffer.h"

#include <glad/glad.h>
#include <iostream>

Framebuffer::Framebuffer(unsigned int windowWidth, unsigned int windowHeight, bool doDepthTest, int colorBufferAmount)
{
	depthTest = doDepthTest;

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create Color attachment(s) to the FBO
	FCO.resize(colorBufferAmount);
	glGenTextures(colorBufferAmount, FCO.data());

	for(unsigned int i = 0; i < colorBufferAmount; i++)
	{
		glBindTexture(GL_TEXTURE_2D, FCO[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		// Attach texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, FCO[i], 0);
	}

	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	std::vector<unsigned int> attachments;
	for(unsigned int i = 0; i < colorBufferAmount; i++)
	{
		attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
	}
	glDrawBuffers(colorBufferAmount, attachments.data());

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BindBuffer(glm::vec3 clearColor)
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if(depthTest)
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
	} 
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

void Framebuffer::BindTexture(unsigned int textureSlot, unsigned int colorBufferIndex)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, FCO[colorBufferIndex]);
}