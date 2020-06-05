#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "SceneManager.h"
#include "Scene.h"

GameObject::GameObject(const std::string& name, const std::string& tag, const std::string& collisionLayer)
	:m_Name{ name },
	m_Tag{ tag },
	m_CollisionLayer{ collisionLayer },
	m_ShouldDelete{ false },
	m_Children{},
	m_IsActive{true}
{
}

GameObject::~GameObject()
{
	for (BaseComponent* pCOmponent : m_Components)
	{
		SAFE_DELETE(pCOmponent);
	}
}

void GameObject::Initialize()
{
	for (BaseComponent* component : m_Components)
	{
		component->Initialize();
	}
}

void GameObject::FixedUpdate()
{
	for (BaseComponent* component : m_Components)
	{
		component->FixedUpdate();
	}
}

void  GameObject::Update()
{
	for (BaseComponent* component : m_Components)
	{
		component->Update();
	}
}

void  GameObject::Render() const
{
	for (BaseComponent* component : m_Components)
	{
		component->Render();
	}
}

void  GameObject::AddComponent(BaseComponent* pComponent)
{
	for (auto* component : m_Components)
	{
		if (component == pComponent)
		{
			std::cout << "This object already contains this type of component.\n";
			return;
		}
	}
	m_Components.push_back(pComponent);
	pComponent->SetGameObject(this);
}

void GameObject::AddChild(GameObject* pGameObject)
{
	m_Children.push_back(pGameObject);
}

void GameObject::SetName(const std::string& name)
{
	m_Name = name;
}

void GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

void GameObject::SetCollisionLayer(const std::string& layer)
{
	m_CollisionLayer = layer;
}

void GameObject::SetDelete(bool shouldDelete)
{
	m_ShouldDelete = shouldDelete;
}

void GameObject::SetActive(bool active)
{
	m_IsActive = active;

	//Also do it for the children
	for (GameObject* pChild : m_Children)
	{
		pChild->SetActive(active);
	}
}

const std::string& GameObject::GetName() const
{
	return m_Name;
}

const std::string& GameObject::GetTag() const
{
	return m_Tag;
}

const std::string& GameObject::GetCollisionLayer() const
{
	return m_CollisionLayer;
}

const std::vector<GameObject*>& GameObject::GetChildren() const
{
	return m_Children;
}

//Please make sure gameobjects dont have the same name
GameObject* GameObject::GetChild(const std::string& name) const
{
	for (GameObject* pChild : m_Children)
	{
		if (pChild->GetName() == name)
			return pChild;
	}
	return nullptr;
}

GameObject* GameObject::GetChild(int index) const
{
	return m_Children[index];
}

bool GameObject::GetDelete() const
{
	return m_ShouldDelete;
}

bool GameObject::IsActive() const
{
	return m_IsActive;
}