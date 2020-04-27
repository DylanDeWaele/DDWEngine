#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"

GameObject::GameObject(const std::string& name, const std::string& tag, const std::string& collisionLayer)
	:m_Name{ name },
	m_Tag{ tag },
	m_CollisionLayer{ collisionLayer },
	m_ShouldDelete{false}
{
}

GameObject::~GameObject()
{
	for (BaseComponent* component : m_Components)
	{
		delete component;
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
	pComponent->SetParent(this);
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

bool GameObject::GetDelete() const
{
	return m_ShouldDelete;
}
