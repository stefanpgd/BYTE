#include "DungeonGeneration.h"
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
}

void DungeonGeneration::GenerateDungeon()
{

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