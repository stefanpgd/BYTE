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
std::vector<Enemy*> enemyRefs;

GameManager::GameManager()
{
	camera = new Camera(glm::vec3(0.0, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	player = new Player(camera);

	dungeonInfo.width = 17;
	dungeonInfo.height = 40;
	dungeonInfo.dungeonScale = 1.5f;
	dungeonInfo.minWalkers = 40;
	dungeonInfo.maxWalkers = 50;
	dungeonInfo.minWalkerLifeTime = 15;
	dungeonInfo.maxWalkerLifeTime = 30;
	dungeonInfo.turnProbability = 0.4f;
	dungeonInfo.enemySpawns = 10;

	dungeonGen = new DungeonGeneration(dungeonInfo);
	player->transform.Position = glm::vec3(dungeonGen->GetPlayerSpawnPosition(), 0.0f);

	transform.Position = glm::vec3(0.0f, 0.0f, -0.05f);
	transform.Scale = glm::vec3(10.0f);

	std::vector<glm::vec2> enemyPositions = dungeonGen->GetEnemySpawnPositions();

	for(int i = 0; i < dungeonInfo.enemySpawns; i++)
	{
		Enemy* enemy = new Enemy(&player->transform, this);
		enemy->transform.Position.x = enemyPositions[i].x;
		enemy->transform.Position.y = enemyPositions[i].y;

		enemyRefs.push_back(enemy);
	}
}

void GameManager::AddGameObject(GameObject* gameObject)
{
	queuedObjects.push_back(gameObject);
}

void GameManager::Update(float deltaTime)
{
	GameTime::Update();

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

	float dist = glm::length(player->transform.Position - glm::vec3(dungeonGen->GetExitPosition(), 0.0f));

	if (dist < 0.5 && enemyRefs.size() == 0)
	{
		GameObject* base = dynamic_cast<GameObject*>(player);

		for (GameObject* gameObject : gameObjects)
		{
			if (gameObject != base)
			{
				gameObject->markedForDelete = true;
			}
		}

		dungeonGen->Delete();
		dungeonGen = new DungeonGeneration(dungeonInfo);

		player->transform.Position = glm::vec3(dungeonGen->GetPlayerSpawnPosition(), 0.0f);

		std::vector<glm::vec2> enemyPositions = dungeonGen->GetEnemySpawnPositions();

		for (int i = 0; i < dungeonInfo.enemySpawns; i++)
		{
			Enemy* enemy = new Enemy(&player->transform, this);
			enemy->transform.Position.x = enemyPositions[i].x;
			enemy->transform.Position.y = enemyPositions[i].y;
			enemyRefs.push_back(enemy);
		}
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

void GameManager::RemoveEnemy(Enemy* enemy)
{
	enemyRefs.erase(std::remove(enemyRefs.begin(), enemyRefs.end(), enemy), enemyRefs.end());
}