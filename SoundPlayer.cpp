
#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
    Engine.init();
    LoadFiles();
}

SoLoud::handle SoundPlayer::Play(SoundName Name)
{
    for (Sound& SoundItem : Sounds)
    {
        if (SoundItem.Name == Name)
        {
            SoundItem.Handle = Engine.play(SoundItem.Obj);
            return SoundItem.Handle;
        }
    }
    return SoLoud::handle();
}

void SoundPlayer::StopAllExceptBackground()
{
    for (Sound& SoundItem : Sounds)
    {
        if (SoundItem.Name != SoundName::BACKGROUND)
        {
            if (SoundItem.Handle)
            {
                Engine.stopAudioSource(SoundItem.Obj);
            }
        }
    }

}

void SoundPlayer::LoadFiles()
{
    for (Sound& SoundItem : Sounds)
    {
        SoundItem.Obj.setLooping(SoundItem.IsLooped);
        SoundItem.Obj.setVolume(SoundItem.Volume);
        SoundItem.Obj.load(SoundItem.FileName);
    }
}