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
	//Set object to delete to true
	pObject->SetDelete(true);
	return true;
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
	//Changged this particular for loop to prevent a crash when adding new game objects inside the update
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::CleanUp()
{
	for (GameObject* pGameObject : m_Objects)
	{
		if (pGameObject->GetDelete()) 
		{
			m_Objects.erase(std::find(m_Objects.begin(), m_Objects.end(), pGameObject));
			SAFE_DELETE(pGameObject);
		}
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
