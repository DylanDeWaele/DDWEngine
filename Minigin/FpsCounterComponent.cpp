#include "MiniginPCH.h"
#include "FpsCounterComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "GameTime.h"

FpsCounterComponent::FpsCounterComponent()
	: BaseComponent{},
	m_Frames{},
	m_Counter{}
{
}

void FpsCounterComponent::Initialize()
{
}

void FpsCounterComponent::Update()
{
	m_Frames++; //Once we get here again a new frame has passed

	//Every 0.25 seconds we update the counter
	m_Counter += GameTime::GetInstance().GetElapsedTime();
	if (m_Counter > 250) //250 ms
	{
		m_pParent->GetComponent<TextComponent>()->SetText(std::to_string(m_Frames * 4)); //*4 because we only take a quarter of a second
		m_Counter = 0;
		m_Frames = 0;
	}
}

void FpsCounterComponent::Render() const
{
}
