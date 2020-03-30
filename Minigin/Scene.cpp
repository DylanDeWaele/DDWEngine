#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() 
{
	for (SceneObject* pObject : m_Objects) 
	{
		SAFE_DELETE(pObject);
	}
}

void Scene::Add(SceneObject* object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float elapsedTime)
{
	for (auto& object : m_Objects)
	{
		object->Update(elapsedTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

