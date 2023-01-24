#pragma once

#include <string>

#include "fmod.hpp"

namespace FMOD
{
	class Sound;
	class Channel;
}

namespace FMOD
{
	namespace Studio
	{
		class EventInstance;
		class Channel;
		class Sound;
		class Bank;
		class System;
	}
}

class Audio
{
public:
	static void PlaySound(std::string filePath, FMOD_MODE playMode = FMOD_2D);

private:
	static void Initialize();
	static void Update();
	static void Shutdown();

	static inline FMOD::Studio::System* audioSystem;
	static inline FMOD::System* coreSystem;

	friend class Engine;
};