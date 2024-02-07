#pragma once

#include "soloud.h"
#include "soloud_wav.h"

enum class SoundName
{
	BACKGROUND,
	BOW_READY,
	WALK, 

	NEAR_BATS,
	NEAR_WAMPUS_SLEEP,
	NEAR_WAMPUS_AWAKE,
};

struct Sound
{
	SoundName Name;
	const char* FileName;
	SoLoud::Wav Obj;
	SoLoud::handle Handle{0};
	float Volume{ 1.0 };
	bool IsLooped{ false };
	Sound(float Volume, SoundName Name, const char* FileName, bool IsLooped = false) :
		Volume(Volume), Name(Name), FileName(FileName), IsLooped(IsLooped) {};
};

class SoundPlayer
{
public:
	SoundPlayer();
	SoLoud::Soloud Engine;
	SoLoud::handle Play(SoundName Name);
	void StopAllExceptBackground();
private:
	Sound Sounds[5]
	{
		{2, SoundName::BACKGROUND, "BACKGROUND.wav", true},
		{0.1,SoundName::WALK, "WALK.wav"},
		{0.05, SoundName::BOW_READY, "BOW_READY.wav"},

		{1,SoundName::NEAR_BATS, "NEAR_BATS.wav", true},
		{2,SoundName::NEAR_WAMPUS_SLEEP, "NEAR_WAMPUS_SLEEP.wav", true},
		{2,SoundName::NEAR_WAMPUS_AWAKE, "NEAR_WAMPUS_AWAKE.wav", true},
	};
	void LoadFiles();
};