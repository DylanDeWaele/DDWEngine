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

	//Also pushback the objects children
	const std::vector<GameObject*>& children = object->GetChildren();
	for (GameObject* pChild : children)
	{
		Add(pChild);
	}
}

bool Scene::Remove(GameObject* pObject)
{
	//Set object to delete to true
	pObject->SetDelete(true);
	return true;
}

void Scene::Initialize()
{
	if (SceneManager::GetInstance().GetActiveScene() == this)
	{
		for (auto& object : m_Objects)
		{
			object->Initialize();
		}
	}
}

void Scene::FixedUpdate()
{
	if (SceneManager::GetInstance().GetActiveScene() == this)
	{
		for (auto& object : m_Objects)
		{
			if (object->IsActive())
				object->FixedUpdate();
		}
	}
}

void Scene::Update()
{
	//Changged this particular for loop to prevent a crash when adding new game objects inside the update
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		//Only do when this scene is still the active scene
		if (SceneManager::GetInstance().GetActiveScene() != this)
			return;

		if (m_Objects[i]->IsActive())
			m_Objects[i]->Update();
	}
}

void Scene::Render() const
{
	if (SceneManager::GetInstance().GetActiveScene() == this)
	{
		for (const auto& object : m_Objects)
		{
			//Only do when this scene is still the active scene
			if (object->IsActive())
				object->Render();
		}
	}
}

void Scene::CleanUp()
{
	if (SceneManager::GetInstance().GetActiveScene() == this)
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
