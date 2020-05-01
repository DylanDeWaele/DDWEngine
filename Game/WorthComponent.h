#pragma once
#include <BaseComponent.h>
class WorthComponent : public BaseComponent
{
public:
	//Ctor
	WorthComponent(int worth);
	//Dtor
	virtual ~WorthComponent() = default;

	//Public member functions
	virtual void Update() override;

	//Getters
	int GetWorth() const;

private:
	//Private datamembers
	int m_Worth;
};

