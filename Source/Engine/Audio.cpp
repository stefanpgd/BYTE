#include "Engine/Audio.h"

#include "fmod_studio.hpp"
#include "fmod_errors.h"
#include "fmod_common.h"

/// <summary>
/// filePath starts from 'Assets/Audio/'. 
/// </summary>
void Audio::PlaySound(std::string filePath, FMOD_MODE playMode)
{
	FMOD::Sound* sound = nullptr;
	std::string path = "Assets/Audio/" + filePath;

	coreSystem->createSound(path.c_str(), playMode, 0, &sound);

	FMOD::Channel* channel = nullptr;
	coreSystem->getChannel(0, &channel);
	coreSystem->playSound(sound, 0, false, &channel);
}

void Audio::Initialize()
{
	FMOD::Studio::System::create(&audioSystem);
	audioSystem->getCoreSystem(&coreSystem);

	coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);
	audioSystem->initialize(2048, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
}

void Audio::Update()
{
	audioSystem->update();
}

void Audio::Shutdown()
{
	audioSystem->release();
}