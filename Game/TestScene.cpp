//Always include the engine pch file
#include "MiniginPCH.h"

#include "TestScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "Scene.h"
#include "Font.h"

TestScene::TestScene()
	: m_pBackground{ nullptr },
	m_pFPSCounter {nullptr},
	m_pLogo{nullptr},
	m_pText{nullptr}
{

	Initialize();
}

TestScene::~TestScene()
{
	SAFE_DELETE(m_pFont);
}

void TestScene::DeleteBackground()
{
	SAFE_DELETE(m_pBackground);
}

void TestScene::Initialize()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	
	//Font that we will use for texts
	m_pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
	//m_pBackground = new GameObject{};
	//m_pBackground->AddComponent(new TransformComponent{ {0,0,0} });
	//m_pBackground->AddComponent(new TextureComponent{ "background.jpg" });
	//scene.Add(m_pBackground);
	
	//go = std::make_shared<GameObject>();
	//go->AddComponent(new TransformComponent{ {216,180,0} });
	//go->AddComponent(new TextureComponent{ "logo.png" });
	//scene.Add(go);
	//
	//go = std::make_shared<GameObject>();
	//go->AddComponent(new TransformComponent{ {80, 20,0} });
	//go->AddComponent(new TextComponent{ "Programming 4 Assignment", font });
	//scene.Add(go);
	//
	//auto fpsCounter = std::make_shared<GameObject>();
	//fpsCounter->AddComponent(new TransformComponent{ {0,0,0} });
	//fpsCounter->AddComponent(new TextComponent{ "00", font });
	//fpsCounter->AddComponent(new FpsCounterComponent{});
	//scene.Add(fpsCounter);
}
