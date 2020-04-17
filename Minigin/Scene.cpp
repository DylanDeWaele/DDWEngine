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

bool Scene::Remove(GameObject* pObject)
{
	std::vector<GameObject*>::iterator foundObject{ std::find(m_Objects.begin(), m_Objects.end(), pObject) };
	if (foundObject != m_Objects.end())
	{
		m_Objects.erase(foundObject);
		SAFE_DELETE(pObject);
		return true;
	}
	std::cout << "ERROR - Trying to remove a Game Object that does not exist\n";
	return false;
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

GameObject* Scene::GetGameObjectWithTag(const std::string& tag) const
{
	//Loop over all gameobjects
	for (GameObject* pGameObject : m_Objects)
	{
		//Return the one where the tag is equal
		if (pGameObject->GetTag() == tag)
			return pGameObject;
	}
	std::cout << "ERROR - GetGameObjectWithTag(" << tag << ") - No GameObject was found with this tag\n";
	return nullptr;
}

const std::vector<GameObject*> Scene::GetGameObjecstWithTag(const std::string& tag) const
{
	std::vector<GameObject*> found{};
	//Loop over all gameobjects
	for (GameObject* pGameObject : m_Objects)
	{
		//Return the one where the tag is equal
		if (pGameObject->GetTag() == tag)
			found.push_back(pGameObject);
	}
	if (found.size() == 0)
		std::cout << "ERROR - GetGameObjectsWithTag(" << tag << ") - No GameObjects were found with this tag\n";

	return found;
}
