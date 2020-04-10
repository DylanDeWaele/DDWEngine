#pragma once
#include "Singleton.h"
class GameTime : public Singleton<GameTime>
{
public:
	//Ctor
	GameTime();
	//Dtor
	virtual ~GameTime() = default;
	//Public member functions
	//Getter
	float GetElapsedTime() const;
	//Setter
	void SetElapsedTime(float elapsedTime);
private:
	float m_ElapsedTime;
};

