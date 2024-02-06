#pragma once
#include <vector>
#include <queue>
#include <thread>

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
	const int Duration;
	char* Memory;
	SoundMem(const char* FileName, int Duration) : FileName(FileName), Duration(Duration) {};
};

void Play(SoundMem** SoundMemPtr);


class SoundPlayer
{
public:
	SoundPlayer() {	LoadFiles();}
	void operator()(std::queue<int>* PlayQueue);

private:
	SoundMem** SoundMem1Ptr = new SoundMem* { nullptr };
	SoundMem** SoundMem2Ptr = new SoundMem* { nullptr };
	SoundMem** SoundMem3Ptr = new SoundMem* { nullptr };
	SoundMem** SoundMem4Ptr = new SoundMem* { nullptr };

	std::thread* Worker1 = new std::thread{ Play, SoundMem1Ptr };
	std::thread* Worker2 = new std::thread{ Play, SoundMem2Ptr };
	std::thread* Worker3 = new std::thread{ Play, SoundMem3Ptr };
	std::thread* Worker4 = new std::thread{ Play, SoundMem4Ptr };

	void LoadFiles();
	SoundMem Sounds[2]
	{
		{"BOW_READY.wav", 1350}, 
		{"WALK.wav", 2700}
	};

};