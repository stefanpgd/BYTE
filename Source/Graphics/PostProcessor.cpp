#include "PostProcessor.h"
#include "ShaderProgram.h"
#include "ScreenQuad.h"
#include "Framebuffer.h"

#include <glad/glad.h>
#include <imgui.h>

PostProcessor::PostProcessor(unsigned int windowWidth, unsigned int windowHeight)
{
	screenQuad = new ScreenQuad();

	screenShader = new ShaderProgram("screen.vert", "screen.frag");
	gaussianBlurShader = new ShaderProgram("screen.vert", "gaussianBlur.frag");

	// Apply constant uniform data // 
	screenShader->Bind();
	screenShader->SetInt("sceneTexture", 0);
	screenShader->SetInt("bloomTexture", 1);

	// Setup objects for post-processing //
	SetupBloom(windowWidth, windowHeight);
}

void PostProcessor::PostProcess(Framebuffer* sceneBuffer)
{
	// Apply post-processing effects to scene buffer // 
	ApplyBloom(sceneBuffer);

	// Enable default buffer // 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Final post-processing pass (Chromatic Aberration, HDR, Gamma Correction) // 
	screenShader->Bind();
	screenShader->SetFloat("exposure", exposure);

	// Chromatic Aberration settings //
	screenShader->SetVec2("rOffset", redOffset);
	screenShader->SetVec2("gOffset", greenOffset);
	screenShader->SetVec2("bOffset", blueOffset);
	screenShader->SetBool("centeredCA", chromaticAberrationFromCenter);
	screenShader->SetFloat("centeredCAStrength", chromaticAberrationCenterStrength);

	sceneBuffer->BindTexture(0, 0);

	glActiveTexture(GL_TEXTURE1); 
	glBindTexture(GL_TEXTURE_2D, bloomColorBuffer[bloomBufferIndex]); 
	screenQuad->Render();
}

void PostProcessor::DebugDrawImGui()
{
	ImGui::Begin("Screen Settings");
	ImGui::DragFloat("Exposure", &exposure, 0.01f, 0.01f);
	ImGui::End();
}

void PostProcessor::SetupBloom(unsigned int windowWidth, unsigned int windowHeight)
{
	glGenFramebuffers(2, bloomFBO);
	glGenTextures(2, bloomColorBuffer);
	for(unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, bloomFBO[i]);
		glBindTexture(GL_TEXTURE_2D, bloomColorBuffer[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bloomColorBuffer[i], 0);
	}
}

void PostProcessor::ApplyBloom(Framebuffer* sceneBuffer)
{
	bool horizontal = true;
	int amount = 5;

	gaussianBlurShader->Bind();
	gaussianBlurShader->SetInt("image", 0);
	for(unsigned int i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, bloomFBO[horizontal]);
		gaussianBlurShader->SetInt("horizontal", horizontal);

		if(i == 0)
		{
			sceneBuffer->BindTexture(0, 1);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, bloomColorBuffer[!horizontal]);
		}

		screenQuad->Render();
		horizontal = !horizontal;
	}

	bloomBufferIndex = horizontal;
}