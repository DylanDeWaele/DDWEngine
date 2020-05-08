#include "MiniginPCH.h"
#include "BoxColliderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include <SDL.h>

BoxColliderComponent::BoxColliderComponent(float width, float height, bool isTrigger)
	: BaseComponent{},
	m_Rect{},
	m_IsTrigger{ isTrigger },
	m_IsTriggered{ false },
	m_pCollidedObject{nullptr}
{
	m_Rect.width = width;
	m_Rect.height = height;
}

void BoxColliderComponent::Update()
{
	//Follow the parent movement - AFTER physics have been calculated and executed on it
	FollowParent();
}

void BoxColliderComponent::Render() const
{
	SDL_Rect sdlRect = m_Rect.GetSDLRect();
	//DEBUG RENDERING
	SDL_Renderer* pRenderer = Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(pRenderer, &sdlRect);
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
}

const DDWRect& BoxColliderComponent::GetRect() const
{
	return m_Rect;
}

bool BoxColliderComponent::IsTrigger() const
{
	return m_IsTrigger;
}

bool BoxColliderComponent::IsTriggered() const
{
	return m_IsTriggered;
}

GameObject* BoxColliderComponent::GetCollidedObject() const
{
	return m_pCollidedObject;
}

void BoxColliderComponent::SetTriggered(bool triggered)
{
	m_IsTriggered = triggered;
}

void BoxColliderComponent::SetIsTrigger(bool isTrigger)
{
	m_IsTrigger = isTrigger;
}

void BoxColliderComponent::SetCollidedObject(GameObject* pOther)
{
	m_pCollidedObject = pOther;
}

void BoxColliderComponent::SetWidthAndHeight(float width, float height)
{
	m_Rect.width = width;
	m_Rect.height = height;
}

void BoxColliderComponent::FollowParent()
{
	//Could optimize this but dont want to include the whole vec3 hpp for it
	//Only if the parent has a transformComponent
	TransformComponent* pTransform = m_pGameObject->GetComponent<TransformComponent>();
	if (pTransform)
	{
		m_Rect.x = pTransform->GetRenderPosition().x;
		m_Rect.y = pTransform->GetRenderPosition().y;
	}
	else
	{
		std::cout << "ERROR: A BoxCollider is trying to follow an object that does not have a TransformComponent!\n";
	}
}