#pragma once
#include "BaseComponent.h"
#include <string>
#include <vector>

class Sound;

class SoundComponent final : public BaseComponent
{
public:
	//Ctors
	SoundComponent(const std::vector<Sound*>& sounds);

	//Dtor
	virtual ~SoundComponent();

	//Public member functions	
	virtual void Update() override;
	virtual void Initialize() override;

	void Play(int index);
	void Pause(int index);
	void Stop(int index);

	void AddSound(Sound* pSound);
	void RemoveSound(int index);

	void SetVolume(int volume);

private:
	//Private datamembers	
	std::vector<Sound*> m_Sounds;
};

