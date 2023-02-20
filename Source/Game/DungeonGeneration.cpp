#include "DungeonGeneration.h"

#include "Engine/Utilities.h"
#include "Graphics/SpriteRenderer.h"
#include "Engine/BoxCollider.h"

DungeonGeneration::DungeonGeneration(DungeonGenerationInfo info)
{
	dungeonInfo = info;

	for(int y = 0; y < dungeonInfo.height; y++)
	{
		for(int x = 0; x < dungeonInfo.width; x++)
		{
			mapIDs.push_back(MapElements::Wall);
		}
	}

	spriteRenderer = new SpriteRenderer("wall.png", &dungeonTransform);

	dungeonTransform.Scale = glm::vec3(dungeonInfo.dungeonScale);

	GenerateDungeon();
	PostProcess();
	AddGameElements();
}

void DungeonGeneration::GenerateDungeon()
{
	std::vector<Walker> walkers;
	int walkerCount = RandomInRange(dungeonInfo.minWalkers, dungeonInfo.maxWalkers);

	for(int i = 0; i < walkerCount; i++)
	{
		int lifeTime = RandomInRange(dungeonInfo.minWalkerLifeTime, dungeonInfo.maxWalkerLifeTime);

		Walker w(dungeonInfo.width, dungeonInfo.height, lifeTime, dungeonInfo.turnProbability);
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
			mapIDs[pos.x + pos.y * dungeonInfo.width] = MapElements::Floor;
		}
	}
}

void DungeonGeneration::PostProcess()
{
	// Clean up 3x3 walls //
	for(unsigned int y = 0; y < dungeonInfo.height; y++)
	{
		for(unsigned int x = 0; x < dungeonInfo.width; x++)
		{
			bool foundFloor = false;

			for(int nx = -1; nx < 2; nx++)
			{
				for(int ny = -1; ny < 2; ny++)
				{
					if(!OutOfBounds(x + nx, y + ny))
					{
						if(mapIDs[(x + nx) + (y + ny) * dungeonInfo.width] == MapElements::Floor)
						{
							foundFloor = true;
						}
					}
				}
			}

			if(!foundFloor)
			{
				mapIDs[x + y * dungeonInfo.width] = MapElements::Empty;
			}
		}
	}
}

void DungeonGeneration::AddGameElements()
{
	// Determine spawn Position Player //
	for (unsigned int y = 0; y < dungeonInfo.height; y++)
	{
		for (unsigned int x = 0; x < dungeonInfo.width; x++)
		{
			if (mapIDs[x + y * dungeonInfo.width] == MapElements::Floor)
			{
				playerSpawnTile.x = x * dungeonInfo.dungeonScale;
				playerSpawnTile.y = y * dungeonInfo.dungeonScale;
			}
		}
	}

	// Determine spawn Position Player //
	for (unsigned int y = 0; y < dungeonInfo.height; y++)
	{
		for (unsigned int x = 0; x < dungeonInfo.width; x++)
		{
			if (mapIDs[x + y * dungeonInfo.width] == MapElements::Wall)
			{
				glm::vec3 position = glm::vec3(x * dungeonInfo.dungeonScale, y * dungeonInfo.dungeonScale, 0.0f);
				glm::vec2 size = glm::vec2(dungeonInfo.dungeonScale / 2.0f);

				BoxCollider* collider = new BoxCollider(position, size, "wall");
				mapColliders.push_back(collider);
			}
		}
	}

	while (enemySpawnPoints.size() < 5)
	{
		int randomX = RandomInRange(0, dungeonInfo.width);
		int randomY = RandomInRange(0, dungeonInfo.height);

		if (mapIDs[randomX + randomY * dungeonInfo.width] == MapElements::Floor)
		{
			glm::vec2 pos = glm::vec2(randomX, randomY);
			pos *= dungeonInfo.dungeonScale;

			if (pos != playerSpawnTile)
			{
				enemySpawnPoints.push_back(pos);
			}
		}
	}
}

bool DungeonGeneration::OutOfBounds(unsigned int x, unsigned int y)
{
	return x < 0 || x > dungeonInfo.width - 1 || y < 0 || y > dungeonInfo.height - 1;
}

void DungeonGeneration::Draw(Camera* camera)
{
	for(unsigned int y = 0; y < dungeonInfo.height; y++)
	{
		for(unsigned int x = 0; x < dungeonInfo.width; x++)
		{
			if(mapIDs[x + y * dungeonInfo.width] == MapElements::Wall)
			{
				dungeonTransform.Position = glm::vec3(x * dungeonInfo.dungeonScale, y * dungeonInfo.dungeonScale, -0.03f);
				spriteRenderer->Draw(camera);
			}
		}
	}
}

glm::vec2 DungeonGeneration::GetPlayerSpawnPosition()
{
	return playerSpawnTile;
}

const std::vector<glm::vec2>& DungeonGeneration::GetEnemySpawnPositions()
{
	return enemySpawnPoints;
}

Walker::Walker(unsigned int levelWidth, unsigned int levelHeight, int lifeTime, float turn) : 
	levelWidth(levelWidth), levelHeight(levelHeight), lifeTime(lifeTime), turnProbability(turn)
{
	position.x = levelWidth / 2;
	position.y = levelHeight / 2;

	directionIndex = RandomInRange(0, 4);
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