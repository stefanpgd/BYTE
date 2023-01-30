#pragma once

class Renderer;
class GameManager;
class CollisionSystem;

class Engine
{
public:
	Engine();

	void Run();

private:
	Renderer* renderer;
	GameManager* gameManager;
	CollisionSystem* collisionSystem;
};