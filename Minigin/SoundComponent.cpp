#include "MiniginPCH.h"
#include "SoundComponent.h"
#include <SDL_Mixer.h>
#include "Music.h"
#include "SoundEffect.h"

//Documentation
//https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php

SoundComponent::SoundComponent(const std::vector<Sound*>& sounds)
	: m_Sounds{ sounds }
{
}

SoundComponent::~SoundComponent()
{
	for (Sound* pSound : m_Sounds)
	{
		SAFE_DELETE(pSound);
	}
}

void SoundComponent::Update()
{
}

void SoundComponent::Initialize()
{
	for (Sound* pSound : m_Sounds)
	{
		if (pSound->ShouldPlayOnStart()) 
		{
			pSound->Stop();
			pSound->Play();
		}
	}
}

void SoundComponent::Play(int index)
{
	m_Sounds[index]->Play();
}
void SoundComponent::Pause(int index)
{
	m_Sounds[index]->Pause();
}

void SoundComponent::Stop(int index)
{
	m_Sounds[index]->Stop();
}

void SoundComponent::AddSound(Sound* pSound)
{
	m_Sounds.push_back(pSound);
}

void SoundComponent::RemoveSound(int index)
{
	m_Sounds.erase(m_Sounds.begin() + index);
}

//Max volume = 128
void SoundComponent::SetVolume(int volume)
{
	Mix_VolumeMusic(volume);

	for (Sound* pSound : m_Sounds)
	{
		if (pSound->GetType() == Sound::Type::SoundEffect)
			Mix_VolumeChunk(dynamic_cast<SoundEffect*>(pSound)->GetChunk(), volume);
	}
}
