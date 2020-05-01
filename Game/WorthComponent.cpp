#include "WorthComponent.h"

WorthComponent::WorthComponent(int worth)
	: m_Worth{worth}
{
}

void WorthComponent::Update()
{
}

int WorthComponent::GetWorth() const
{
	return m_Worth;
}
