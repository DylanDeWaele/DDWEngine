#include "MiniginPCH.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "GameObject.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

void TextComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		delete m_pTexture;

		const SDL_Color color = { 255,255,255 };
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = new Texture2D{ texture };
		m_NeedsUpdate = false;
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

TextComponent::TextComponent(const std::string& text, Font* pFont)
	: BaseComponent{},
	m_NeedsUpdate(true),
	m_Text(text),
	m_pFont(pFont),
	m_pTexture(nullptr)
{

}

TextComponent::~TextComponent()
{
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pTexture);
}
