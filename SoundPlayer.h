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
	NEAR_PIT,
};

struct Sound
{
	Sound() {};
	Sound(float Volume, SoundName Name, const char* FileName, bool IsLooped = false) :
		Volume(Volume), Name(Name), FileName(FileName), IsLooped(IsLooped) {};
	
	SoundName Name;
	const char* FileName;
	SoLoud::Wav Obj;
	SoLoud::handle Handle{0};
	float Volume{ 1.0 };
	bool IsLooped{ false };
};

class SoundPlayer
{
public:
	SoundPlayer();

	SoLoud::Soloud Engine;
	Sound* GetSound(SoundName Name);
	SoLoud::handle Play(SoundName Name, bool Paused = false);
	SoLoud::handle PlayFadeIn(SoundName Name, float Seconds);
	void StopAllExceptBackground();
private:
	Sound Sounds[7]
	{
		{2,		SoundName::BACKGROUND,			"BACKGROUND.wav",			true},
		{0.1,	SoundName::WALK,				"WALK.wav"},
		{0.2,	SoundName::BOW_READY,			"BOW_READY.wav"},

		{1,		SoundName::NEAR_BATS,			"NEAR_BATS.wav",			true},
		{1.4,	SoundName::NEAR_WAMPUS_SLEEP,	"NEAR_WAMPUS_SLEEP.wav",	true},
		{2,		SoundName::NEAR_WAMPUS_AWAKE,	"NEAR_WAMPUS_AWAKE.wav",	true},
		{0.6,	SoundName::NEAR_PIT,			"NEAR_PIT.wav",				true},
	};
	void LoadFiles();
};