#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class TransformComponent : public BaseComponent
{
public:
	//Ctor
	TransformComponent(const glm::vec2& position, const glm::vec2& rotation = { 0,0 }, const glm::vec2& scale = { 1,1 });
	//Dtor
	virtual ~TransformComponent() = default;
	//Public member functions
	//Setters
	void SetPosition(const glm::vec2& position);
	void SetRotation(const glm::vec2& rotation);
	void SetScale(const glm::vec2& scale);
	//Getters
	const glm::vec2& GetPosition();
	const glm::vec2& GetRotation();
	const glm::vec2& GetScale();

	void Move(float x, float y);

	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const override;

private:
	//Private datamembers
	glm::vec2 m_Position;
	glm::vec2 m_Rotation;
	glm::vec2 m_Scale;
};
