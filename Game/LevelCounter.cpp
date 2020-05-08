#include "GamePCH.h"
#include "LevelCounter.h"

#include "TransformComponent.h"
#include "TextComponent.h"

#include "ResourceManager.h"

LevelCounter::LevelCounter(float x, float y, int levelCount, const std::string& name, const std::string& tag, const std::string& collisionLayer)
	: Prefab{ name, tag, collisionLayer }
{
	m_pGameObject->AddComponent(new TransformComponent{ {x,y} });
	m_pGameObject->AddComponent(new TextComponent{ "0" + std::to_string(levelCount), ResourceManager::GetInstance().LoadFont("Lingua.otf", 28) });
}
