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
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const;

	//Getters
	int GetWorth() const;

private:
	//Private datamembers
	int m_Worth;
};

