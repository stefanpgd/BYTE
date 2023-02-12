#include "DungeonGeneration.h"

#include "Engine/Utilities.h"
#include "Graphics/SpriteRenderer.h"

DungeonGeneration::DungeonGeneration(unsigned int width, unsigned int height, float dungeonScale)
{
	mapWidth = width;
	mapHeight = height;
	this->dungeonScale = dungeonScale;

	for(int y = 0; y < mapHeight; y++)
	{
		for(int x = 0; x < mapWidth; x++)
		{
			mapIDs.push_back(MapElements::Wall);
		}
	}

	spriteRenderer = new SpriteRenderer("wall.png", &dungeonTransform);

	dungeonTransform.Scale = glm::vec3(dungeonScale);

	GenerateDungeon();
	PostProcess();
}

void DungeonGeneration::GenerateDungeon()
{
	std::vector<Walker> walkers;
	int walkerCount = mapWidth * 3;

	for(int i = 0; i < walkerCount; i++)
	{
		Walker w(mapWidth, mapHeight);
		walkers.push_back(w);
	}

	for(Walker& walker : walkers)
	{
		while(walker.IsAlive())
		{
			walker.Walk();

			if(walker.IsOutOfBounds())
			{
				continue;
			}

			glm::ivec2 pos = walker.GetPosition();
			mapIDs[pos.x + pos.y * mapWidth] = MapElements::Floor;
		}
	}
}

void DungeonGeneration::PostProcess()
{
	// Clean up 3x3 walls //
	for(unsigned int y = 0; y < mapHeight; y++)
	{
		for(unsigned int x = 0; x < mapWidth; x++)
		{
			bool foundFloor = false;

			for(int nx = -1; nx < 2; nx++)
			{
				for(int ny = -1; ny < 2; ny++)
				{
					if(!OutOfBounds(x + nx, y + ny))
					{
						if(mapIDs[(x + nx) + (y + ny) * mapWidth] == MapElements::Floor)
						{
							foundFloor = true;
						}
					}
				}
			}

			if(!foundFloor)
			{
				mapIDs[x + y * mapWidth] = MapElements::Empty;
			}
		}
	}
}

bool DungeonGeneration::OutOfBounds(unsigned int x, unsigned int y)
{
	return x < 0 || x > mapWidth - 1 || y < 0 || y > mapHeight - 1;
}

void DungeonGeneration::Draw(Camera* camera)
{
	for(unsigned int y = 0; y < mapHeight; y++)
	{
		for(unsigned int x = 0; x < mapWidth; x++)
		{
			if(mapIDs[x + y * mapWidth] == MapElements::Wall)
			{
				dungeonTransform.Position = glm::vec3(x * dungeonScale, y * dungeonScale, -0.03f);
				spriteRenderer->Draw(camera);
			}
		}
	}
}

Walker::Walker(unsigned int levelWidth, unsigned int levelHeight) : levelWidth(levelWidth), levelHeight(levelHeight)
{
	position.x = levelWidth / 2;
	position.y = levelHeight / 2;

	directionIndex = RandomInRange(0, 4);
	lifeTime = RandomInRange(levelWidth, int(levelWidth * 4));
}

void Walker::Walk()
{
	lifeTime--;
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

	// Check Bounds, we want to leave a 1 space gap with the edges //
	if(IsOutOfBounds())
	{
		lifeTime = 0;
	}
}

bool Walker::IsAlive()
{
	return lifeTime > 0;
}

glm::ivec2 Walker::GetPosition()
{
	return position;
}

bool Walker::IsOutOfBounds()
{
	return position.x < 1 || position.x >= levelWidth - 1 || position.y < 1 || position.y >= levelHeight - 1;
}