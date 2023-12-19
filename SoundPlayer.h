// License file: COPYING.WTFPL. Author: diego1812@gmail.com
#pragma once

#include <vector>

#include "soloud.h"
#include "soloud_wav.h"

enum class SoundName
{
	BACKGROUND,

	PLAYER_WALK, 
	PLAYER_DIE,
	PLAYER_FALL,

	NEAR_BATS,
	NEAR_WAMPUS_SLEEP,
	NEAR_WAMPUS_AWAKE,
	NEAR_PIT,

	BOW_READY,
	BOW_STRING,
	ARROW_WHOOSH,
	SAD_TROMBONE,

	WAMPUS_WAKE_UP,
	WAMPUS_DIE,
	BATS_IN_FACE,
};

struct Sound
{
	Sound() {};
	Sound(float Volume, SoundName Name, const char* FileName, bool IsLooped = false) :
		Volume(Volume), Name(Name), FileName(FileName), IsLooped(IsLooped) {};
	
	SoundName Name;
	const char* FileName;
	SoLoud::Wav Obj;
	std::vector<SoLoud::handle> Handles;
	float Volume{ 1.0 };
	bool IsLooped{ false };
};

class SoundPlayer
{
public:
	SoundPlayer();

	SoLoud::Soloud Engine;
	Sound* GetSound(SoundName Name);
	void Play(SoundName Name, bool Paused = false);
	void PlayFadeIn(SoundName Name, float Seconds);
	void PlayFadeOut(SoundName Name, float Seconds);
	void PlayFadeOut(SoLoud::handle Handle, float Seconds);
	void StopAllExceptBackground();
	void FadeOutAllExceptBackground(int Seconds);
private:
	Sound Sounds[15]
	{
		{1.5,	SoundName::BACKGROUND,			"Sounds\\BACKGROUND.wav",			true},

		{0.1,	SoundName::PLAYER_WALK,			"Sounds\\PLAYER_WALK.wav"				},
		{0.8,	SoundName::PLAYER_DIE,			"Sounds\\PLAYER_DIE.wav"				},
		{0.5,	SoundName::PLAYER_FALL,			"Sounds\\PLAYER_FALL.wav"				},

		{1,		SoundName::NEAR_BATS,			"Sounds\\NEAR_BATS.wav",			true},
		{1.2,	SoundName::NEAR_WAMPUS_SLEEP,	"Sounds\\NEAR_WAMPUS_SLEEP.wav",	true},
		//{0.8,	SoundName::NEAR_WAMPUS_AWAKE,	"Sounds\\NEAR_WAMPUS_AWAKE.wav",	true},
		{0.6,	SoundName::NEAR_WAMPUS_AWAKE,	"Sounds\\NEAR_WAMPUS_AWAKE_2.wav",	true},
		{0.6,	SoundName::NEAR_PIT,			"Sounds\\NEAR_PIT.wav",				true},

		{0.2,	SoundName::BOW_READY,			"Sounds\\BOW_READY.wav"					},
		{1,		SoundName::BOW_STRING,			"Sounds\\BOW_STRING.wav",				},
		{1,		SoundName::ARROW_WHOOSH,		"Sounds\\ARROW_WHOOSH.wav",				},
		{1,		SoundName::SAD_TROMBONE,		"Sounds\\SAD_TROMBONE.wav",				},

		{1,		SoundName::WAMPUS_WAKE_UP,		"Sounds\\WAMPUS_WAKE_UP.wav",			},
		{1,		SoundName::WAMPUS_DIE,			"Sounds\\WAMPUS_DIE.wav",				},
		{1,		SoundName::BATS_IN_FACE,		"Sounds\\BATS_IN_FACE.wav",				},
	};
	void LoadFiles();
};