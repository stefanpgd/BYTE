#pragma once

class Renderer;
class GameManager;
class CollisionSystem;
class UISystem;

class Engine
{
public:
	Engine();

	void Run();

private:
	Renderer* renderer;
	GameManager* gameManager;
	CollisionSystem* collisionSystem;
	UISystem* uiSystem;
};