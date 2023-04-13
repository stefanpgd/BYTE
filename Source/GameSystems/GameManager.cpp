#include "GameSystems/GameManager.h"
#include "GameSystems/GameObject.h"
#include "GameSystems/GameTime.h"

#include "Engine/Camera.h"
#include "Engine/Utilities.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Graphics/SpriteRenderer.h"

// Game Elements //
#include "Game/PlayerPaddle.h"
#include "Game/Ball.h"

#include <imgui.h>

PlayerPaddle* player;
Ball* ball;

SpriteRenderer* background;
Transform backgroundTransform;

GameManager::GameManager()
{
	camera = new Camera(glm::vec3(0.0, 0.0f, 45.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	background = new SpriteRenderer("background.png", &backgroundTransform);
	backgroundTransform.Scale = glm::vec3(38.0f);
	backgroundTransform.Position.z = -0.01f;

	player = new PlayerPaddle();
	ball = new Ball();
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
}

void GameManager::Draw()
{
	background->Draw(camera);

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

	ImGui::Begin("Camera");
	ImGui::DragFloat3("Camera Position", &camera->Position[0]);
	ImGui::End();
#endif
}