#pragma once
#include <vector>

#include "Engine/Transform.h"

class GameObject;
class SpriteRenderer;
class Camera;
class BoxCollider;

enum class MapElements
{
	Wall,
	Floor,
	Empty
};

struct DungeonGenerationInfo
{
	unsigned int width;
	unsigned int height;
	float dungeonScale;

	int minWalkers;
	int maxWalkers;

	int minWalkerLifeTime;
	int maxWalkerLifeTime;

	float turnProbability;
};

class DungeonGeneration
{
public:
	DungeonGeneration(DungeonGenerationInfo dungeonInfo);

	void Draw(Camera* camera);

	glm::vec2 GetPlayerSpawnPosition();

private:
	void GenerateDungeon();
	void PostProcess();
	void AddGameElements();

	bool OutOfBounds(unsigned int x, unsigned int y);

	std::vector<MapElements> mapIDs;
	std::vector<BoxCollider*> mapColliders;

	DungeonGenerationInfo dungeonInfo;

	Transform dungeonTransform;
	SpriteRenderer* spriteRenderer;
	glm::vec2 playerSpawnTile;
};

class Walker
{
public:
	Walker(unsigned int levelWidth, unsigned int levelHeight, int lifeTime, float turn);

	void Walk();
	bool IsAlive();
	glm::ivec2 GetPosition();
	bool IsOutOfBounds();

private:
	int lifeTime;
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
	float turnProbability;
};