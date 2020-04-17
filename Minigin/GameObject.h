#pragma once
#include "BaseComponent.h"
#include <vector>
#include <string>
#include <iostream>

class Texture2D;
class GameObject final
{
public:
	//Ctor
	GameObject();
	
	//Dtor
	virtual ~GameObject();
	
	//Rule of 5
	GameObject(const GameObject & other) = delete;
	GameObject(GameObject && other) = delete;
	GameObject& operator=(const GameObject & other) = delete;
	GameObject& operator=(GameObject && other) = delete;

	//Public member functions
	void Initialize();
	void FixedUpdate();
	void Update();
	void Render() const;

	//Setters
	void AddComponent(BaseComponent* pComponent);
	void SetTag(const std::string& tag);
	void SetCollisionLayer(const std::string& layer);

	//Getters
	template <class Component>
	Component* GetComponent() const;
	const std::string& GetTag() const;
	const std::string& GetCollisionLayer() const;

private:
	std::string m_Tag;
	std::string m_CollisionLayer;
	std::vector<BaseComponent*> m_Components;
};

template<class Component>
inline Component* GameObject::GetComponent() const
{
	//Code example found in the overlord engine from graphics programming 2
	const type_info& ti = typeid(Component);
	for (auto* component : m_Components)
	{
		if (component && typeid(*component) == ti)
			return static_cast<Component*>(component);
	}

	std::cout << "Component of type: " << typeid(Component).name() << " could not be found\n";

	return nullptr;
}

