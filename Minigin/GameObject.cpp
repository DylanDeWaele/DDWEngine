#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"

GameObject::GameObject()
	: m_Tag{"Default"},
	m_CollisionLayer{"Default"}
{
}

GameObject::~GameObject()
{
	for(BaseComponent* component : m_Components)
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

void GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

void GameObject::SetCollisionLayer(const std::string& layer)
{
	m_CollisionLayer = layer;
}

const std::string& GameObject::GetTag() const
{
	return m_Tag;
}

const std::string& GameObject::GetCollisionLayer() const
{
	return m_CollisionLayer;
}
