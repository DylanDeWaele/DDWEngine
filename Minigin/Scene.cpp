#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) 
	: m_Name(name)
{}

Scene::~Scene() 
{
	for (GameObject* pObject : m_Objects) 
	{
		SAFE_DELETE(pObject);
	}
}

void Scene::Add(GameObject* object)
{
	m_Objects.push_back(object);
}

void Scene::Initialize()
{
	for (auto& object : m_Objects)
	{
		object->Initialize();
	}
}

void Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Update()
{
	for (auto& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

const std::string& Scene::GetName() const
{
	return m_Name;
}

const std::vector<GameObject*>& Scene::GetObjects() const
{
	return m_Objects;
}
