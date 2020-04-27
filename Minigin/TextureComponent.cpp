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
	if (m_Flipped)
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Width, m_Height, 0, SDL_FLIP_HORIZONTAL);
	else
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Width, m_Height);
}

void TextureComponent::SetTexture(const std::string& filename, float width, float height)
{
	delete m_pTexture;
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	if (width != 0) m_Width = width;
	if (height != 0) m_Height = height;
}

void TextureComponent::SetFlipped(bool flipped)
{
	m_Flipped = flipped;
}

TextureComponent::TextureComponent(const std::string& filename, float width, float height)
	: BaseComponent{},
	m_Width{ width },
	m_Height{ height },
	m_Flipped{false}
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

TextureComponent::~TextureComponent()
{
	SAFE_DELETE(m_pTexture);
}


