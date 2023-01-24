#include "GameManager.h"
#include "GameObject.h"
#include "../Engine/Camera.h"
#include "../Engine/Utilities.h"
#include "../Engine/Input.h"

#include "../Game/Player.h"

GameManager::GameManager()
{
	camera = new Camera(glm::vec3(0.0, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	player = new Player(camera);
}

void GameManager::Update(float deltaTime)
{
	camera->Update(deltaTime);
	player->Update(deltaTime);
}

void GameManager::Draw()
{
	player->Draw(camera);
}

void GameManager::ImGuiDraw()
{
#if _DEBUG
	player->ImGuiDraw();
#endif
}