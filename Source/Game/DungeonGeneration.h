#pragma once
#include <vector>

#include "Engine/Transform.h"

class GameObject;
class SpriteRenderer;
class Camera;

enum class MapElements
{
	Wall,
	Floor,
	Empty
};

class DungeonGeneration
{
public:
	DungeonGeneration(unsigned int width, unsigned int height, float dungeonScale);

	void Draw(Camera* camera);

private:
	void GenerateDungeon();
	void PostProcess();

	bool OutOfBounds(unsigned int x, unsigned int y);

	std::vector<MapElements> mapIDs;

	Transform dungeonTransform;
	SpriteRenderer* spriteRenderer;
	unsigned int mapWidth;
	unsigned int mapHeight;
	float dungeonScale;
};

class Walker
{
public:
	Walker(unsigned int levelWidth, unsigned int levelHeight);

	void Walk();
	bool IsAlive();
	glm::ivec2 GetPosition();
	bool IsOutOfBounds();

private:
	int lifeTime = 5;
	glm::ivec2 position;

	unsigned int levelWidth;
	unsigned int levelHeight;

	// Directions:
	// 0 : Up
	// 1 : Right
	// 2 : Down
	// 3 : Left
	glm::ivec2 directions[4] =
	{
		glm::ivec2(0, 1),
		glm::ivec2(1, 0),
		glm::ivec2(0, -1),
		glm::ivec2(-1, 0)
	};

	int directionIndex;
	float turnProbability = 0.4f;
};