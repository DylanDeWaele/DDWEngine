#pragma once
#include "BaseComponent.h"

#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)


class TransformComponent : public BaseComponent
{
public:
	//Ctor
	TransformComponent(const glm::vec3& position, const glm::vec3& rotation = { 0,0,0 }, const glm::vec3& scale = { 1,1,1 });
	//Dtor
	virtual ~TransformComponent() = default;
	//Public member functions
	//Setters
	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);
	//Getters
	const glm::vec3& GetPosition();
	const glm::vec3& GetRotation();
	const glm::vec3& GetScale();

	virtual void Update(float elapsedTime) override;
	virtual void Render() const override;

private:
	//Private datamembers
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};
