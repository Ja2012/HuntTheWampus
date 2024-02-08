
#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
    Engine.init();
    LoadFiles();
}

SoLoud::handle SoundPlayer::Play(SoundName Name, bool Paused)
{
    Sound* Item = GetSound(Name);
    Item->Handle = Engine.play(Item->Obj, -1, 0, Paused);
    return Item->Handle;
}

void SoundPlayer::StopAllExceptBackground()
{
    for (Sound& Item : Sounds)
    {
        if (Item.Name != SoundName::BACKGROUND)
        {
            Engine.stopAudioSource(Item.Obj);
        }
    }

}

Sound* SoundPlayer::GetSound(SoundName Name)
{
    for (Sound& Item : Sounds)
    {
        if (Item.Name == Name)
        {
            return &Item;
        }
    }
}

SoLoud::handle SoundPlayer::PlayFadeIn(SoundName Name, float Seconds)
{
    SoLoud::handle Handle;
    Sound* Item = GetSound(Name);
    Handle = Engine.play(Item->Obj, 0, 0, true);
    Engine.fadeVolume(Handle, Item->Volume, Seconds);
    Engine.setPause(Handle, false);
    return Handle;
}

void SoundPlayer::LoadFiles()
{
    for (Sound& Item : Sounds)
    {
        Item.Obj.setLooping(Item.IsLooped);
        Item.Obj.setVolume(Item.Volume);

        Item.Obj.load(Item.FileName);
    }
}