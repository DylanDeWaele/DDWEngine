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
			if (m_pActiveScene)
				m_pActiveScene->CleanUp();

			m_pPreviousScene = m_pActiveScene;
			m_pActiveScene = pScene;
			m_pActiveScene->Initialize(); //Reinitialize the scene
		}
	}
}

Scene* SceneManager::GetActiveScene() const
{
	return m_pActiveScene;
}

Scene* SceneManager::GetSceneByName(const std::string& name) const
{
	for (Scene* pScene : m_Scenes)
	{
		if (pScene->GetName() == name)
			return pScene;
	}
	return nullptr;
}

Scene* SceneManager::GetPreviousScene() const
{
	return m_pPreviousScene;
}

SceneManager::SceneManager()
	: m_pActiveScene{ nullptr },
	m_pPreviousScene{nullptr}
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
