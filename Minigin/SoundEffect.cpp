#include "MiniginPCH.h"
#include "SoundEffect.h"

SoundEffect::SoundEffect(const std::string& fullPath, bool playOnStart)
	:Sound{ Type::SoundEffect , playOnStart},
	m_pSoundEffect{ nullptr }
{
	m_pSoundEffect = Mix_LoadWAV(fullPath.c_str());
	if (!m_pSoundEffect)
		std::cout << "Could not load sound effect file: " << fullPath << '\n';

}

SoundEffect::~SoundEffect()
{
	if (m_pSoundEffect)
		Mix_FreeChunk(m_pSoundEffect);
}

void SoundEffect::Play()
{
	Mix_PlayChannel(-1, m_pSoundEffect, 0);
}

void SoundEffect::Pause()
{
	std::cout << "A sound effect cannot be paused\n";
}

void SoundEffect::Stop()
{
	std::cout << "A sound effect cannot be stopped\n";
}

Mix_Chunk* SoundEffect::GetChunk() const
{
	return m_pSoundEffect;
}
