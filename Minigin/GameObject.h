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
	GameObject(const std::string& name = "GameObject", const std::string& tag = "Default", const std::string& collisionLayer = "Default");
	
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
	void SetName(const std::string& name);
	void SetTag(const std::string& tag);
	void SetCollisionLayer(const std::string& layer);
	void SetDelete(bool shouldDelete);

	//Getters
	template <typename Component>
	Component* GetComponent() const;
	const std::string& GetName() const;
	const std::string& GetTag() const;
	const std::string& GetCollisionLayer() const;
	bool GetDelete() const;

private:
	std::string m_Name;
	std::string m_Tag;
	std::string m_CollisionLayer;
	std::vector<BaseComponent*> m_Components;

	bool m_ShouldDelete;
};

template<typename Component>
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

