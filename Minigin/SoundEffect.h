#pragma once
#include <SDL_Mixer.h>
#include <string>
#include "Sound.h"

class SoundEffect : public Sound
{
public:
	//Ctor
	SoundEffect(const std::string& fullPath, bool playOnStart = false);
	//Dtor
	~SoundEffect();

	//Public member functions
	virtual void Play() override;
	virtual void Pause() override;
	virtual void Stop() override;

	Mix_Chunk* GetChunk() const;

private:
	//Private datamembers
	Mix_Chunk* m_pSoundEffect;
};

