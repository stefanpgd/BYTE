#pragma once
#include <vector>

class Camera;
class Player;
class GameObject;

class GameManager
{
public:
	GameManager();

	static void AddGameObject(GameObject* gameObject);

	void Update(float deltaTime);
	void Draw();
	void ImGuiDraw();

private:
	Camera* camera;
	Player* player;

	static inline std::vector<GameObject*> gameObjects;
};