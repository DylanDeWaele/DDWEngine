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
	virtual void Initialize() = 0;
	virtual void FixedUpdate() = 0; //Physics
	virtual void Update() = 0;
	virtual void Render() const = 0;
	//Setters 
	void SetParent(GameObject* pParent);

protected:
	//Protected datamembers
	GameObject* m_pParent;	
};

