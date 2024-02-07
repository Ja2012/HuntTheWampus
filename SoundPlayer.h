#pragma once

#include "soloud.h"
#include "soloud_wav.h"

enum class SoundName
{
	BOW_READY,
	WALK
};

struct Sound
{
	SoundName Name;
	const char* FileName;
	SoLoud::Wav Obj;
	Sound(SoundName Name, const char* FileName) : Name(Name), FileName(FileName) {};
};

class SoundPlayer
{
public:
	SoundPlayer();
	SoLoud::handle Play(SoundName Name);
private:
	SoLoud::Soloud Engine;
	Sound Sounds[2]
	{
		{SoundName::BOW_READY, "BOW_READY.wav"},
		{SoundName::WALK, "WALK.wav"},
	};
	void LoadFiles();
};