#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <mmsystem.h> // link "winmm.lib"

#include "SoundPlayer.h"

void SoundPlayer::LoadFiles()
{
    for (SoundMem& SoundMem : Sounds)
    {
        int FileSize = std::filesystem::file_size(SoundMem.FileName);
        std::ifstream Stream{ SoundMem.FileName, std::ios_base::binary };
        char* Buffer = new char[FileSize];
        Stream.read(Buffer, FileSize);
        SoundMem.Memory = Buffer;
    }
}

void SoundPlayer::operator()(std::queue<int>* PlayQueue)
{
    while (true)
    {
        if (!PlayQueue->empty())
        {
            PlaySoundA(Sounds[PlayQueue->front()].Memory, nullptr, SND_MEMORY | SND_ASYNC);
            PlayQueue->pop();
        }
    };

}
