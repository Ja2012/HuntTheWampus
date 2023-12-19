
#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
    Engine.init();
    LoadFiles();
}

void SoundPlayer::Play(SoundName Name, bool Paused)
{
    Sound* Item = GetSound(Name);
    SoLoud::handle Handle = Engine.play(Item->Obj, -1, 0, Paused);
    Item->Handles.push_back(Handle);
}

void SoundPlayer::StopAllExceptBackground()
{
    for (Sound& Item : Sounds)
    {
        if (Item.Name != SoundName::BACKGROUND)
        {
            Engine.stopAudioSource(Item.Obj);
            Item.Handles.clear();
        }
    }

}

void SoundPlayer::FadeOutAllExceptBackground(int Seconds)
{
    for (Sound& Item : Sounds)
    {
        if (Item.Name != SoundName::BACKGROUND)
        {
            for (SoLoud::handle Handle: Item.Handles)
            {
                PlayFadeOut(Handle, Seconds);
            }
            Item.Handles.clear();
        }
    }

}

Sound* SoundPlayer::GetSound(SoundName Name)
{
    Sound* Item{};
    for (Sound& Item : Sounds)
    {
        if (Item.Name == Name)
        {
            return &Item;
        }
    }
    return Item;
}
void SoundPlayer::PlayFadeIn(SoundName Name, float Seconds)
{
    Sound* Item = GetSound(Name);
    if (Item->IsLooped and !Item->Handles.empty()) return; // only one loop sound at time

    SoLoud::handle Handle;
    Handle = Engine.play(Item->Obj, 0, 0, true);
    Item->Handles.push_back(Handle);
    Engine.fadeVolume(Handle, Item->Volume, Seconds);
    Engine.setPause(Handle, false);
}

void SoundPlayer::PlayFadeOut(SoundName Name, float Seconds)
{
    Sound* Item = GetSound(Name);
    for (SoLoud::handle Handle: Item->Handles)
    {
        PlayFadeOut(Handle, Seconds);
    }
    Item->Handles.clear();
}

void SoundPlayer::PlayFadeOut(SoLoud::handle Handle, float Seconds)
{
    Engine.fadeVolume(Handle, 0, Seconds);
    Engine.scheduleStop(Handle, Seconds);
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