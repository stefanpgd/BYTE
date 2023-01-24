#include "GameManager.h"
#include "GameObject.h"
#include "../Engine/Camera.h"
#include "../Engine/Utilities.h"
#include "../Engine/Input.h"

GameManager::GameManager()
{
	camera = new Camera(glm::vec3(0.0, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}

void GameManager::Update(float deltaTime)
{
	camera->Update(deltaTime);
}

void GameManager::Draw()
{
	// Draw Calls
}

void GameManager::ImGuiDraw()
{
#if _DEBUG
	// Imgui Draw Calls
#endif
}