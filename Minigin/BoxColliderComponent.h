#pragma once
#include "BaseComponent.h"
#include "Structs.h"

class BoxColliderComponent final : public BaseComponent
{
public:
	//Ctor
	//Width and height starting from the top left of the gameobject
	BoxColliderComponent(float width, float height, bool isTrigger = false);

	//Dtor
	virtual ~BoxColliderComponent() = default;

	//Public member functions	
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const override;

	//Getters
	const DDWRect& GetRect() const;
	//This function tells us whether or not the box collider is a trigger
	bool IsTrigger() const;
	//This function tells us whether or not the trigger has been triggered
	bool IsTriggered() const;

	GameObject* GetCollidedObject() const;

	//Setters
	void SetTriggered(bool triggered);
	void SetCollidedObject(GameObject* pOther);

private:
	//Private datamembers
	DDWRect m_Rect;
	bool m_IsTrigger;
	bool m_IsTriggered;

	//The other object that was last triggered
	GameObject* m_pCollidedObject;

	//Private functions
	void FollowParent();
};

