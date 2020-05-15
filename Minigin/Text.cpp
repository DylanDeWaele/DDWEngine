#include "MiniginPCH.h"
#include "Text.h"
#include "GameObject.h"

//Components
#include "TransformComponent.h"
#include "TextComponent.h"


Text::Text(float x, float y, const std::string& text, Font* pFont, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{name, tag, collisionLayer}
{
	TransformComponent* pTransform = new TransformComponent{ {x,y} };
	TextComponent* pText = new TextComponent{ text, pFont };

	m_pGameObject->AddComponent(pTransform);
	m_pGameObject->AddComponent(pText);
}
