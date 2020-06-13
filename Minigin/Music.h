#pragma once
#include <SDL_Mixer.h>
#include <string>
#include "Sound.h"

class Music : public Sound
{
public:
	//Ctor
	Music(const std::string& fullPath, bool playOnStart = false);
	//Dtor
	~Music();

	//Public member functions
	virtual void Play() override;
	virtual void Pause() override;
	virtual void Stop() override;

private:
	//Private datamembers
	Mix_Music* m_pMusic;
};

