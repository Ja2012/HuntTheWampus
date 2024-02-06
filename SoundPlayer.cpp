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
            if (!*SoundMem1Ptr)
            {
                *SoundMem1Ptr = &Sounds[PlayQueue->front()]; 
            }
            else if (!*SoundMem2Ptr)
            {
                *SoundMem2Ptr = &Sounds[PlayQueue->front()];
            }
            else if (!*SoundMem3Ptr)
            {
                *SoundMem3Ptr = &Sounds[PlayQueue->front()];
            }
            else if (!*SoundMem4Ptr)
            {
                *SoundMem4Ptr = &Sounds[PlayQueue->front()];
            }
            else
            {
                return;
            }
            PlayQueue->pop();
        }
    };

}

void Play(SoundMem** SoundMemPtr)
{
    while (true)
    {
        if (*SoundMemPtr)
        {
            std::cout << SoundMemPtr << '\n';
            PlaySoundA((*SoundMemPtr)->Memory, nullptr, SND_MEMORY | SND_ASYNC);
            //Sleep((*SoundMemPtr)->Duration);
            std::this_thread::sleep_for(std::chrono::milliseconds((*SoundMemPtr)->Duration));
            *SoundMemPtr = nullptr;
        }
    }
};
