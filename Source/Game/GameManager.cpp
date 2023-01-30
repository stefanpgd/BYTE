#include "GameManager.h"
#include "GameObject.h"
#include "../Engine/Camera.h"
#include "../Engine/Utilities.h"
#include "../Engine/Input.h"
#include "../Engine/BoxCollider.h"

#include "../Game/Player.h"
#include "../Graphics/SpriteRenderer.h"

SpriteRenderer* map;
Transform transform;

SpriteRenderer* testCube;
Transform testCubeTransform;
BoxCollider* testCubeCollider;

GameManager::GameManager()
{
	camera = new Camera(glm::vec3(0.0, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	player = new Player(camera);
	map = new SpriteRenderer("testMap1.png", &transform);
	testCube = new SpriteRenderer("blank.png", &testCubeTransform);
	testCubeTransform.Position = glm::vec3(2.0f, 1.0f, -0.03f);
	testCubeCollider = new BoxCollider(testCubeTransform.Position, glm::vec2(1.0f, 1.0f), "wall");

	transform.Position = glm::vec3(0.0f, 0.0f, -0.05f);
	transform.Scale = glm::vec3(10.0f);
}

void GameManager::AddGameObject(GameObject* gameObject)
{
	queuedObjects.push_back(gameObject);
}

void GameManager::Update(float deltaTime)
{
	// Clean up all game objects that have been marked for delete in the last frame // 
	gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
		[](GameObject* g) { return g->markedForDelete; }), gameObjects.end());

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
	testCube->Draw(camera);

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

void TestOnCollision(const std::string& tag)
{
	if(tag == "default")
	{
		testCube->Color = glm::vec3(0.0f, 1.0f, 0.0f);
	}
}