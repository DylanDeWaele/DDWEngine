#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name(name),
	m_Objects{}
{
}

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

void Scene::AddWhileRunning(GameObject* pObject)
{
	Add(pObject);

	pObject->Initialize();
}

bool Scene::Remove(GameObject* pObject)
{
	//Set object to delete to true
	pObject->SetDelete(true);

	//Also delete all children
	return true;
}

void Scene::Initialize()
{
	if (SceneManager::GetInstance().GetActiveScene() == this)
	{
		for (auto& object : m_Objects)
		{
			if (object)
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
		for (size_t i = 0; i < m_Objects.size(); i++)
		{
			GameObject* pObject = m_Objects[i];
			if (pObject)
			{
				if (pObject->GetDelete())
				{
					m_Objects.erase(std::find(m_Objects.begin(), m_Objects.end(), pObject));
					SAFE_DELETE(pObject);
				}
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

	return found;
}
