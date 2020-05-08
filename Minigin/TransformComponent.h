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
	TransformComponent(const glm::vec2& position, float rotation = 0, const glm::vec2& scale = { 1,1 });
	//Dtor
	virtual ~TransformComponent() = default;
	//Public member functions
	//Setters
	void SetPosition(const glm::vec2& position);
	void SetScale(const glm::vec2& scale);
	void SetRotation(float rotation);

	//Getters
	const glm::vec2& GetPosition() const;
	glm::vec2 GetRenderPosition() const;
	const glm::vec2& GetScale() const;
	float GetRotation() const;

	void Translate(float x, float y);
	void Rotate(float rotation);

	virtual void Update() override;

private:
	//Private datamembers
	glm::vec2 m_Position;
	glm::vec2 m_Scale;
	float m_Rotation;
};
