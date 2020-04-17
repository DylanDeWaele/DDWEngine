#include "WorthComponent.h"

WorthComponent::WorthComponent(int worth)
	: m_Worth{worth}
{
}

void WorthComponent::Initialize()
{
}

void WorthComponent::FixedUpdate()
{
}

void WorthComponent::Update()
{
}

void WorthComponent::Render() const
{
}

int WorthComponent::GetWorth() const
{
	return m_Worth;
}
