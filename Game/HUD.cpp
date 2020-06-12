#include "HUD.h"
//Game
#include "Game.h"

//Engine
#include "ResourceManager.h"

//Components
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "HudComponent.h"

//Prefab
#include "Text.h"

//Scene
#include "SceneManager.h"
#include "Scene.h"

HUD::HUD(int playerNr, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	//The hud is an empty gameobject which contains all of these child gameobjects
	//It only contains the hud component which will handle all hud components
	HudComponent* pHUD = new HudComponent{ playerNr };
	m_pGameObject->AddComponent(pHUD);

	//Decide y
	float y = 0;
	switch (playerNr)
	{
	case 0:
		y = Minigin::GetInstance().GetWindowHeight();
		break;
	case 1:
		y = Minigin::GetInstance().GetWindowHeight() - 25;
		break;
	}

	//Initialize background
	const float textureHeight{ 30.f };
	GameObject* pBackground = new GameObject{ "HUD_Background", "HUD" };
	TransformComponent* pBackgroundTransform = new TransformComponent{ {0, y} };
	TextureComponent* pBackgroundTexture = new TextureComponent{ "Black.jpg", Minigin::GetInstance().GetWindowWidth(), textureHeight };
	pBackground->AddComponent(pBackgroundTransform);
	pBackground->AddComponent(pBackgroundTexture);

	//Initialize score text
	float x{ 5.f };
	y -= 5.f;

	Text scoreText = Text{ x,y, "Player " + std::to_string(playerNr + 1) + ": ", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20), "HUD_ScoreText", "HUD" };
	//Initialize score
	y--;
	x += 80.f;
	Text score = Text{ x,y, "00000", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20),"HUD_Score", "HUD" };
	//Initialize health text
	y++;
	x = Minigin::GetInstance().GetWindowWidth() - 90.f;
	Text livesText = Text{ x,y, "Lives: ", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20),"HUD_HealthText", "HUD" };
	//Initialize score
	y--;
	x = Minigin::GetInstance().GetWindowWidth() - 32.5f;
	Text health = Text{ x,y, "03", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20),"HUD_Health", "HUD" };

	//Make them children
	m_pGameObject->AddChild(pBackground);
	m_pGameObject->AddChild(scoreText.GetGameObject());
	m_pGameObject->AddChild(score.GetGameObject());
	m_pGameObject->AddChild(livesText.GetGameObject());
	m_pGameObject->AddChild(health.GetGameObject());
}