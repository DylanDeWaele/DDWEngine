#pragma once
#include "GamePCH.h"
#include "Prefab.h"
class Font;

class HUD : public Prefab
{
public:
	//Ctor
	HUD();

private:
	//2 Game objects
	//Children
	GameObject* m_pBackground;
	GameObject* m_pScoreText;
	GameObject* m_pScore;
	GameObject* m_pHealthText;
	GameObject* m_pHealth;
};

