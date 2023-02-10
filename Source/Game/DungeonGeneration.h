#pragma once
#include <vector>

#include "Engine/Transform.h"

class GameObject;
class SpriteRenderer;
class Camera;

enum class MapElements
{
	Wall,
	Floor
};

class DungeonGeneration
{
public:
	DungeonGeneration(unsigned int width, unsigned int height);

	void Draw(Camera* camera);

private:
	void GenerateDungeon();

	std::vector<MapElements> mapIDs;

	Transform dungeonTransform;
	SpriteRenderer* spriteRenderer;
	unsigned int mapWidth;
	unsigned int mapHeight;
};

class Walker
{
public:
	void Walk();
	bool IsAlive();
	glm::ivec2 GetPosition();

private:
	int lifeTime = 3;
	unsigned int directionIndex = 1;
	glm::ivec2 position = glm::ivec2(4,4);

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
};