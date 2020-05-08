#include "HUD.h"
//Game
#include "Game.h"

//Engine
#include "ResourceManager.h"

//Components
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "HudComponent.h"

//Scene
#include "SceneManager.h"
#include "Scene.h"

HUD::HUD()
	: Prefab{"HUD", "HUD", "Default"},
	m_pBackground{ new GameObject{"HUD_Background", "HUD"} },
	m_pScoreText{ new GameObject{"HUD_ScoreText", "HUD"} },
	m_pScore{ new GameObject{"HUD_Score", "HUD"} },
	m_pHealthText{ new GameObject{"HUD_HealthText", "HUD"} },
	m_pHealth{ new GameObject{"HUD_Health", "HUD"} }
{
	//The hud is an empty gameobject which contains all of these child gameobjects
	//It only contains the hud component which will handle all hud components
	HudComponent* pHUD = new HudComponent{};
	m_pGameObject->AddComponent(pHUD);

	//Initialize background
	const float textureHeight{ 30.f };
	TransformComponent* pBackgroundTransform = new TransformComponent{ {0, Minigin::GetInstance().GetWindowHeight()} };
	TextureComponent* pBackgroundTexture = new TextureComponent{ "Black.jpg", Minigin::GetInstance().GetWindowWidth(), textureHeight };
	m_pBackground->AddComponent(pBackgroundTransform);
	m_pBackground->AddComponent(pBackgroundTexture);

	//Initialize score text
	float x{ 5.f };
	float y{ Minigin::GetInstance().GetWindowHeight() - 5.f };
	TransformComponent* pScoreTextTransform = new TransformComponent{ {x,  y} };
	TextComponent* pScoreText = new TextComponent{ "Score:", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };
	m_pScoreText->AddComponent(pScoreTextTransform);
	m_pScoreText->AddComponent(pScoreText);
	//Initialize score
	y--;
	x += 60.f;
	TransformComponent* pScoreTransform = new TransformComponent{ {x, y} };
	TextComponent* pScore = new TextComponent{ "00000", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };
	m_pScore->AddComponent(pScoreTransform);
	m_pScore->AddComponent(pScore);

	//Initialize health text
	y++;
	x = Minigin::GetInstance().GetWindowWidth() - 90.f;
	TransformComponent* pHealthTextTransform = new TransformComponent{ {x, y} };
	TextComponent* pHealthText = new TextComponent{ "Lives:", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };
	m_pHealthText->AddComponent(pHealthTextTransform);
	m_pHealthText->AddComponent(pHealthText);
	//Initialize score
	y--;
	x = Minigin::GetInstance().GetWindowWidth() - 32.5f;
	TransformComponent* pHealthTransform = new TransformComponent{ {x, y} };
	TextComponent* pHealth = new TextComponent{ "03", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };
	m_pHealth->AddComponent(pHealthTransform);
	m_pHealth->AddComponent(pHealth);

	//Make them children
	m_pGameObject->AddChild(m_pBackground);
	m_pGameObject->AddChild(m_pScoreText);
	m_pGameObject->AddChild(m_pScore);
	m_pGameObject->AddChild(m_pHealthText);
	m_pGameObject->AddChild(m_pHealth);
}