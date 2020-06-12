#pragma once
#include "Singleton.h"
class GameMode : public Singleton<GameMode>
{
public:
	enum class Mode 
	{
		Singleplayer,
		Coop,
		Versus
	};

	//Ctor
	GameMode();
	//Dtor
	virtual ~GameMode() = default;
	//Public member functions
	//Getter
	const Mode& GetGameMode() const;
	//Setter
	void SetGameMode(Mode gameMode);

private:
	Mode m_GameMode;
};

