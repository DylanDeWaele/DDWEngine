#include "GamePCH.h"
#include "SelectionPointer.h"

//Components
#include "TransformComponent.h"
#include "TextureComponent.h"

SelectionPointer::SelectionPointer(float x, float y, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	const float bubbleSize = 27.5f;

	m_pGameObject->AddComponent(new TransformComponent{ {x,y} });
	m_pGameObject->AddComponent(new TextureComponent{ "Bubble.png", bubbleSize ,bubbleSize });
}
