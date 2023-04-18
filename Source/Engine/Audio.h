#pragma once

#include <string>
#include "fmod.hpp"
#include "fmod_studio.hpp"
#include "fmod_errors.h"
#include "fmod_common.h"

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
	static FMOD::Channel* PlaySound(std::string filePath, float volume = 1.0f, FMOD_MODE playMode = FMOD_2D);

private:
	static void Initialize();
	static void Update();
	static void Shutdown();

	static inline FMOD::Studio::System* audioSystem;
	static inline FMOD::System* coreSystem;

	friend class Engine;
};