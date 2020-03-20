#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "GameObject.h"

void TextureComponent::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}

void TextureComponent::Render() const
{
	const glm::vec3 pos = m_pParent->GetComponent<TransformComponent>()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

TextureComponent::TextureComponent(const std::string& filename)
	: BaseComponent{}
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}


