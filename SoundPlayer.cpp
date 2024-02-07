
#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
    Engine.init();
    LoadFiles();
}

SoLoud::handle SoundPlayer::Play(SoundName Name)
{
    for (Sound& Sound : Sounds)
    {
        if (Sound.Name == Name)
        {
            return Engine.play(Sound.Obj);
        }
    }
    return SoLoud::handle();
}

void SoundPlayer::LoadFiles()
{
    for (Sound& Sound: Sounds)
    {
        Sound.Obj.load(Sound.FileName);
    }
}