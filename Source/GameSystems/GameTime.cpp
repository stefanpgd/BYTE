#include "GameSystems/GameTime.h"

void GameTime::Update()
{
	if(pauseTicks > 0)
	{
		pauseTicks--;
	}
}

void GameTime::SetTimeScale(float scaleFactor)
{
	gameTimeScale = scaleFactor;
}

float GameTime::GetTimeScale()
{
	if(pauseTicks > 0)
	{
		return 0.0f;
	}

	return gameTimeScale;
}

void GameTime::QueuePauseTicks(int ticks)
{
	pauseTicks += ticks;
}
