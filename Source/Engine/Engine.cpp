#include "Engine/Engine.h"

// Graphics //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Graphics/Renderer.h"
#include "Graphics/Model.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/UISystem.h"

// Engine // 
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "Engine/Transform.h"
#include "Engine/CollisionSystem.h"

// STD & External libraries // 
#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <cassert>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// Game // 
#include "GameSystems/GameManager.h"

static void GLFWErrorCallback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Engine::Engine()
{
	srand(time(nullptr));

#if _DEBUG
	glfwSetErrorCallback(GLFWErrorCallback);
#endif

	glfwInit();

	renderer = new Renderer("Breakout - Chaotic Evil");
	collisionSystem = new CollisionSystem();
	uiSystem = new UISystem();
	gameManager = new GameManager();

	Audio::Initialize();
	Input::Initialize(renderer->GetWindow());

	// Initialize ImGui // 
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(renderer->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Engine::Run()
{
	bool isRunning = true;
	GLFWwindow* window = renderer->GetWindow();

	static float deltaTime = 0.0f;
	static std::chrono::high_resolution_clock clock;
	static auto t0 = std::chrono::time_point_cast<std::chrono::milliseconds>((clock.now())).time_since_epoch();

	while (isRunning)
	{
		auto t1 = std::chrono::time_point_cast<std::chrono::milliseconds>((clock.now())).time_since_epoch();
		deltaTime = (t1 - t0).count() * .001;
		t0 = t1;

		// Start //
		renderer->StartFrame();

		// Update //
		Audio::Update();
		gameManager->Update(deltaTime);
		collisionSystem->Update();

		// Drawing //
		gameManager->Draw();
		collisionSystem->Draw(gameManager->camera);
		uiSystem->Draw();
		gameManager->ImGuiDraw();

		renderer->RenderFrame();

		glfwPollEvents();
		if(glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			isRunning = false;
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}