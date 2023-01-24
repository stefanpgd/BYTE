#pragma once

class Renderer;
class GameManager;

class Engine
{
public:
	Engine();

	void Run();

private:
	Renderer* renderer;
	GameManager* gameManager;
};