#include "GameManager.h"
#include "GameObject.h"
#include "../Engine/Camera.h"
#include "../Engine/Utilities.h"
#include "../Engine/Input.h"

#include "../Game/Player.h"
#include "../Graphics/SpriteRenderer.h"

SpriteRenderer* map;
Transform transform;

GameManager::GameManager()
{
	camera = new Camera(glm::vec3(0.0, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	player = new Player(camera);
	map = new SpriteRenderer("testMap1.png", &transform);

	transform.Position = glm::vec3(0.0f, 0.0f, -0.05f);
	transform.Scale = glm::vec3(10.0f);
}

void GameManager::Update(float deltaTime)
{
	camera->Update(deltaTime);
	player->Update(deltaTime);
}

void GameManager::Draw()
{
	map->Draw(camera);
	player->Draw(camera);
}

void GameManager::ImGuiDraw()
{
#if _DEBUG
	player->ImGuiDraw();
#endif
}