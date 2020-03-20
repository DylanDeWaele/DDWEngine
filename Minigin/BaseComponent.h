#pragma once
#include <memory>
class GameObject;
class BaseComponent //Abstract class
{
public:
	//Ctor
	BaseComponent();
	//Dtor
	virtual ~BaseComponent() = default;
	//Rule of 5
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	//Public member functions
	virtual void Update(float elapsedTime) = 0;
	virtual void Render() const = 0;
	//Setters 
	void SetParent(GameObject* pParent);

protected:
	GameObject* m_pParent;
};

