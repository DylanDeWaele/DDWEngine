#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "SDL.h"

void TextureComponent::Initialize()
{
}

void TextureComponent::FixedUpdate()
{
}

void TextureComponent::Update()
{
}

void TextureComponent::Render() const
{
	const glm::vec2 pos = m_pParent->GetComponent<TransformComponent>()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Width, m_Height);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

TextureComponent::TextureComponent(const std::string& filename, float width, float height)
	: BaseComponent{},
	m_Width{ width },
	m_Height{ height }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

TextureComponent::~TextureComponent()
{
	SAFE_DELETE(m_pTexture);
}


