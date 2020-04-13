#include "GamePCH.h"
#include "BulletLifeComponent.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"

BulletLifeComponent::BulletLifeComponent(float lifeTime)
	: m_Lifetime{lifeTime},
	m_CurrentTime{}
{

}

void BulletLifeComponent::Initialize()
{
}

void BulletLifeComponent::FixedUpdate()
{
}

void BulletLifeComponent::Update()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();
	std::cout << m_CurrentTime << '\n';
	if (m_CurrentTime > m_Lifetime) 
	{
		//Remove the bullet from the gameobject list
		SceneManager::GetInstance().GetActiveScene()->Remove(m_pParent);
		//Handle the deletion ourselves
		SAFE_DELETE(m_pParent);
	}
}

void BulletLifeComponent::Render() const
{
}
