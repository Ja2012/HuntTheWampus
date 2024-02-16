#pragma once

#include "soloud.h"
#include "soloud_wav.h"

enum class SoundName
{
	BACKGROUND,
	WALK, 

	NEAR_BATS,
	NEAR_WAMPUS_SLEEP,
	NEAR_WAMPUS_AWAKE,
	NEAR_PIT,

	BOW_READY,
	BOW_STRING,
	ARROW_WHOOSH,

	WAMPUS_WAKE_UP,
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
	Sound Sounds[10]
	{
		{2,		SoundName::BACKGROUND,			"BACKGROUND.wav",			true},
		{0.1,	SoundName::WALK,				"WALK.wav"						},

		{1,		SoundName::NEAR_BATS,			"NEAR_BATS.wav",			true},
		{1.4,	SoundName::NEAR_WAMPUS_SLEEP,	"NEAR_WAMPUS_SLEEP.wav",	true},
		{2,		SoundName::NEAR_WAMPUS_AWAKE,	"NEAR_WAMPUS_AWAKE.wav",	true},
		{0.6,	SoundName::NEAR_PIT,			"NEAR_PIT.wav",				true},

		{0.2,	SoundName::BOW_READY,			"BOW_READY.wav"					},
		{1,		SoundName::BOW_STRING,			"BOW_STRING.wav",				},
		{1,		SoundName::ARROW_WHOOSH,		"ARROW_WHOOSH.wav",				},

		{1,		SoundName::WAMPUS_WAKE_UP,		"WAMPUS_WAKE_UP.wav",			},
	};
	void LoadFiles();
};