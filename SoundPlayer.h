#pragma once
#include <vector>
#include <queue>

enum class SoundName
{
	//AMBIENT,
	BOW_READY,
	//BOW_SHOOT,
	WALK,
	//BATS_HELLO,
	//BATS_MOVE
};


struct SoundMem
{
	const char* FileName;
	char* Memory;
	SoundMem(const char* FileName) : FileName(FileName) {};
};

class SoundPlayer
{
public:
	SoundPlayer() {	LoadFiles();}
	void operator()(std::queue<int>* PlayQueue);

private:
	void LoadFiles();
	SoundMem Sounds[2]
	{
		{"BOW_READY.wav"}, 
		{"WALK.wav"}
	};

};