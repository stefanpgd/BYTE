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

	void GenerateDungeon();
	void Draw(Camera* camera);

private:
	std::vector<MapElements> mapIDs;

	Transform dungeonTransform;
	SpriteRenderer* spriteRenderer;
	unsigned int mapWidth;
	unsigned int mapHeight;
};