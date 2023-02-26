#pragma once
#include <vector>

class Camera;
class Player;
class GameObject;
class Enemy;

class GameManager
{
public:
	GameManager();

	static void AddGameObject(GameObject* gameObject);

	void Update(float deltaTime);
	void Draw();
	void ImGuiDraw();

	// Very placeholder //
	void RemoveEnemy(Enemy* enemy);

	Camera* camera;
private:
	Player* player;

	static inline std::vector<GameObject*> gameObjects;
	static inline std::vector<GameObject*> queuedObjects;
};