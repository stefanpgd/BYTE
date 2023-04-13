#include "Graphics/Renderer.h"

#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Graphics/Framebuffer.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/PostProcessor.h"

Renderer::Renderer(const std::string& windowName)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialize GLAD // 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Error: Failed to initialize GLAD!\n");
		return;
	}

	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sceneBuffer = new Framebuffer(windowWidth, windowHeight, true, 2);
	postProcessor = new PostProcessor(windowWidth, windowHeight);
}

GLFWwindow* Renderer::GetWindow()
{
	return window;
}

unsigned int Renderer::GetWindowWidth()
{
	return windowWidth;
}

unsigned int Renderer::GetWindowHeight()
{
	return windowHeight;
}

void Renderer::StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	sceneBuffer->BindBuffer(glm::vec3(0.0f));
}

void Renderer::RenderFrame()
{
	postProcessor->PostProcess(sceneBuffer);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}