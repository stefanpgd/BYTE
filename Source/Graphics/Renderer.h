#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer;
class PostProcessor;

class Renderer
{
public: 
	Renderer(const std::string& windowName);

	GLFWwindow* GetWindow();
	static unsigned int GetWindowWidth();
	static unsigned int GetWindowHeight();

	void StartFrame();
	void RenderFrame();

private:
	GLFWwindow* window;
	Framebuffer* sceneBuffer;
	PostProcessor* postProcessor;

	static inline int windowWidth = 1080;
	static inline int windowHeight = 720;
};