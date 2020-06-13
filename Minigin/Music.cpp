#include "MiniginPCH.h"
#include "Music.h"

Music::Music(const std::string& fullPath, bool playOnStart)
	: Sound{Type::Music, playOnStart},
	m_pMusic{ nullptr }
{
	m_pMusic = Mix_LoadMUS(fullPath.c_str());
	if (!m_pMusic)
		std::cout << "Could not load music file: " << fullPath << '\n';
}

Music::~Music()
{
	if (m_pMusic) 
	{
		Mix_FreeMusic(m_pMusic);
		m_pMusic = nullptr;
	}

}

void Music::Play()
{
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(m_pMusic, -1); //Looping
}

void Music::Pause()
{
	//If the music is paused
	if (Mix_PausedMusic())
	{
		//Resume the music
		Mix_ResumeMusic();
	}
	//If the music is playing
	else
	{
		//Pause the music
		Mix_PauseMusic();
	}
}

void Music::Stop()
{
	//Stop the music
	Mix_HaltMusic();
}
