#include "Game/GameManager.h"
#include "Game/GameObject.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/GameTime.h"
#include "Game/DungeonGeneration.h"

#include "Engine/Camera.h"
#include "Engine/Utilities.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Graphics/SpriteRenderer.h"

#include <imgui.h>

SpriteRenderer* map;
Transform transform;
DungeonGeneration* dungeonGen;
DungeonGenerationInfo dungeonInfo;

GameManager::GameManager()
{
	camera = new Camera(glm::vec3(0.0, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	player = new Player(camera);

	dungeonInfo.width = 17;
	dungeonInfo.height = 60;
	dungeonInfo.dungeonScale = 1.5f;
	dungeonInfo.minWalkers = 40;
	dungeonInfo.maxWalkers = 50;
	dungeonInfo.minWalkerLifeTime = 15;
	dungeonInfo.maxWalkerLifeTime = 30;
	dungeonInfo.turnProbability = 0.4f;

	dungeonGen = new DungeonGeneration(dungeonInfo);
	player->transform.Position = glm::vec3(dungeonGen->GetPlayerSpawnPosition(), 0.0f);

	transform.Position = glm::vec3(0.0f, 0.0f, -0.05f);
	transform.Scale = glm::vec3(10.0f);

	std::vector<glm::vec2> enemyPositions = dungeonGen->GetEnemySpawnPositions();

	for(int i = 0; i < 5; i++)
	{
		Enemy* enemy = new Enemy(&player->transform);
		enemy->transform.Position.x = enemyPositions[i].x;
		enemy->transform.Position.y = enemyPositions[i].y;
	}

	glm::vec3 a = glm::vec3(1, 0, 0);
	glm::vec2 b = glm::normalize(glm::vec2(0.5, 0.5));

	float dot = glm::dot(a, a);

	printf("%f, %f, %f", b.x, b.y, 0.0f);
}

void GameManager::AddGameObject(GameObject* gameObject)
{
	queuedObjects.push_back(gameObject);
}

void GameManager::Update(float deltaTime)
{
	GameTime::Update();

#if _DEBUG
	dungeonInfo.dungeonScale = 0.1f;

	ImGui::Begin("Dungeon Settings");
	ImGui::DragInt("width", (int*) & dungeonInfo.width, 0.2f, 0, 100);
	ImGui::DragInt("height", (int*)&dungeonInfo.height, 0.2f, 0, 100);
	ImGui::DragInt("min walkers", &dungeonInfo.minWalkers, 0.2f, 0, 100);
	ImGui::DragInt("max walkers", &dungeonInfo.maxWalkers, 0.2f, 0, 100);
	ImGui::DragInt("min lifetime", &dungeonInfo.minWalkerLifeTime, 0.2f, 0, 100);
	ImGui::DragInt("max lifetime", &dungeonInfo.maxWalkerLifeTime, 0.2f, 0, 100);
	ImGui::DragFloat("turn", &dungeonInfo.turnProbability, 0.01f, 0.0f, 1.0f);
#endif

	if (ImGui::Button("Generate"))
	{
		dungeonGen = new DungeonGeneration(dungeonInfo);
	}
	ImGui::End();

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

	float gameTime = deltaTime * GameTime::GetTimeScale();

	// Update Camera & GameObjects // 
	camera->Update(gameTime);
	for(GameObject* obj : gameObjects)
	{
		obj->Update(gameTime);
	}
}

void GameManager::Draw()
{
	//map->Draw(camera);
	dungeonGen->Draw(camera);

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