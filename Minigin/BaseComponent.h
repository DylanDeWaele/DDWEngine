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
	virtual void Initialize() {};
	virtual void FixedUpdate() {}; //Physics
	virtual void Update() = 0; //The only function that is "mandatory" to implement, this way our components are not cluttered with all empty functions (if they arent necesarry)
	virtual void Render() const {};
	//Setters 
	void SetGameObject(GameObject* pGameObject);
	//Getters
	GameObject* GetGameObject() const;

protected:
	//Protected datamembers
	GameObject* m_pGameObject;	
};

