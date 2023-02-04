#pragma once

// GameTime acts as a way to manipulate deltaTime
// without overwriting other systems outside of gameplay that use deltaTime.
// The game manager uses GameTime to edit the updates for GameObjects.
// Besides gameplay purposes it might also be useful for debugging
class GameTime
{
public:
	static void Update();

	static void SetTimeScale(float scaleFactor);
	static float GetTimeScale();

	// For gameplay we might want to 'freeze' the game for impact.
	// So you can do this by queuing 
	static void QueuePauseTicks(int ticks);

private:
	static inline int pauseTicks = 0;
	static inline float gameTimeScale = 1.0f;
};