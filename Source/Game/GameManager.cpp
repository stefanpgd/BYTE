#include "Game/GameManager.h"
#include "Game/GameObject.h"
#include "Game/Player.h"
#include "Game/Enemy.h"

#include "Engine/Camera.h"
#include "Engine/Utilities.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Graphics/SpriteRenderer.h"

#include <imgui.h>

SpriteRenderer* map;
Transform transform;

GameManager::GameManager()
{
	camera = new Camera(glm::vec3(0.0, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	player = new Player(camera);
	map = new SpriteRenderer("testMap1.png", &transform);

	transform.Position = glm::vec3(0.0f, 0.0f, -0.05f);
	transform.Scale = glm::vec3(10.0f);

	for(int i = 0; i < 12; i++)
	{
		Enemy* enemy = new Enemy(&player->transform);
		enemy->transform.Position.x = RandomInRange(-4.0f, 4.0f);
		enemy->transform.Position.y = RandomInRange(-4.0f, 4.0f);
	}
}

void GameManager::AddGameObject(GameObject* gameObject)
{
	queuedObjects.push_back(gameObject);
}

void GameManager::Update(float deltaTime)
{
	// Clean up all game objects that have been marked for delete in the last frame // 
	gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
		[](GameObject* g) 
		{ 
			if(g->markedForDelete)
			{
				delete g;
				return true;
			}
			return false; 
		}), gameObjects.end());

	// Add new objects that have been added to the queue during the last frame //
	for(GameObject* obj : queuedObjects)
	{
		gameObjects.push_back(obj);
	}

	queuedObjects.clear();

	// Update Camera & GameObjects // 
	camera->Update(deltaTime);
	for(GameObject* obj : gameObjects)
	{
		obj->Update(deltaTime);
	}
}

void GameManager::Draw()
{
	map->Draw(camera);

	for(GameObject* obj : gameObjects)
	{
		obj->Draw(camera);
	}
}

void GameManager::ImGuiDraw()
{
#if _DEBUG
	for(GameObject* obj : gameObjects)
	{
		obj->ImGuiDraw();
	}
#endif
}