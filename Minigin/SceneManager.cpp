#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void  SceneManager::Update(float elapsedTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(elapsedTime);
	}
}

void  SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes) 
	{
		SAFE_DELETE(pScene);
	}
}

Scene&  SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	return *scene;
}
