#pragma once
#include "SceneObject.h"
#include "BaseComponent.h"
#include <vector>

class Texture2D;
class GameObject final : public SceneObject
{
public:
	void Update(float elapsedTime) override;
	void Render() const override;

	//Setters
	void AddComponent(BaseComponent* pComponent);

	//Getters
	template <class Component>
	Component* GetComponent() const;

	GameObject() = default;
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

private:
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

	return nullptr;
}

