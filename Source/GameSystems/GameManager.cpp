#include "GameSystems/GameManager.h"
#include "GameSystems/GameObject.h"
#include "GameSystems/GameTime.h"

#include "Engine/Camera.h"
#include "Engine/Utilities.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Graphics/SpriteRenderer.h"
#include "Engine/Audio.h"

// Game Elements //
#include "Game/PlayerPaddle.h"
#include "Game/Ball.h"
#include "Game/Block.h"
#include "Game/PanicButton.h"

#include <imgui.h>

PlayerPaddle* player;
Ball* ball;
PanicButton* panicButton;

bool panicMode = false;

SpriteRenderer* background;
Transform backgroundTransform;

FMOD::Channel* mainMusicTrack;

float startX = -14.2;
float startY = 0.0f;

GameManager::GameManager()
{
	mainMusicTrack = Audio::PlaySound("music.wav");

	camera = new Camera(glm::vec3(0.0, 0.0f, 45.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	background = new SpriteRenderer("background.png", &backgroundTransform);
	backgroundTransform.Scale = glm::vec3(38.0f);
	backgroundTransform.Position.z = -0.01f;

	player = new PlayerPaddle();
	ball = new Ball();
	panicButton = new PanicButton();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Block* b = new Block();
			b->transform.Position = glm::vec3(startX + 4.05f * i, startY + 2.0f * j, 0.0f);
		}
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
				g->OnDestroy();
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

	if (panicButton->pressed && !panicMode)
	{
		panicMode = true;

		ball->PanicMode();
		mainMusicTrack->setVolume(0.0f);
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
	ImGui::DragFloat3("Button Scale", &panicButton->transform.Scale[0]);
	ImGui::DragFloat3("Button Pos", &panicButton->transform.Position[0]);
	ImGui::End();
#endif
}