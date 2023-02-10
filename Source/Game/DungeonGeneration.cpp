#include "DungeonGeneration.h"

#include "Engine/Utilities.h"
#include "Graphics/SpriteRenderer.h"

DungeonGeneration::DungeonGeneration(unsigned int width, unsigned int height)
{
	mapWidth = width;
	mapHeight = height;

	for(int y = 0; y < mapHeight; y++)
	{
		for(int x = 0; x < mapWidth; x++)
		{
			mapIDs.push_back(MapElements::Wall);
		}
	}

	spriteRenderer = new SpriteRenderer("wall.png", &dungeonTransform);

	GenerateDungeon();
}

void DungeonGeneration::GenerateDungeon()
{
	std::vector<Walker> walkers;
	int walkerCount = 1;

	for(int i = 0; i < walkerCount; i++)
	{
		Walker w;
		walkers.push_back(w);
	}

	for(Walker& walker : walkers)
	{
		while(walker.IsAlive())
		{
			walker.Walk();

			glm::ivec2 pos = walker.GetPosition();
			mapIDs[pos.x + pos.y * mapWidth] = MapElements::Floor;
		}
	}
}

void DungeonGeneration::Draw(Camera* camera)
{
	for(unsigned int y = 0; y < mapHeight; y++)
	{
		for(unsigned int x = 0; x < mapWidth; x++)
		{
			if(mapIDs[x + y * mapWidth] == MapElements::Wall)
			{
				dungeonTransform.Position = glm::vec3(x, y, -0.03f);
				spriteRenderer->Draw(camera);
			}
		}
	}
}

void Walker::Walk()
{
	position += directions[directionIndex];

	// get new direction //
	float roll = Random01();
	if(roll < turnProbability)
	{
		// 50/50 chance to go either up or down
		directionIndex = Random01() > 0.5 ? directionIndex - 1 : directionIndex + 1;

		// Modulo to ensure it's within the 0-3 range
		directionIndex = directionIndex % 4;
	}

	lifeTime--;
}

bool Walker::IsAlive()
{
	return lifeTime >= 0;
}

glm::ivec2 Walker::GetPosition()
{
	return position;
}