#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Initialize()
{
	for (Scene* pScene : m_Scenes)
	{
		pScene->Initialize();
	}
}

void SceneManager::FixedUpdate()
{
	m_pActiveScene->FixedUpdate();
}

void  SceneManager::Update()
{
	m_pActiveScene->Update();
}

void  SceneManager::Render()
{
	m_pActiveScene->Render();
}

void SceneManager::CleanUp()
{
	m_pActiveScene->CleanUp();
}

void SceneManager::SetActiveScene(const std::string& sceneName)
{
	for (Scene* pScene : m_Scenes)
	{
		if (pScene->GetName() == sceneName)
		{
			m_pActiveScene = pScene;
			return;
		}
	}
}

Scene* SceneManager::GetActiveScene() const
{
	return m_pActiveScene;
}

SceneManager::SceneManager()
	: m_pActiveScene{ nullptr }
{
}

SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		SAFE_DELETE(pScene);
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	return *scene;
}
