#pragma once
#include "BaseComponent.h"
#include <string>
class Font;
class Texture2D;

class TextComponent final : public BaseComponent
{
public:
	//Ctor
	TextComponent(const std::string& text, Font* pFont);
	
	//Dtor
	virtual ~TextComponent();

	//Public member functions	
	//Setters
	void SetText(const std::string& text);

	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const override;

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	Font* m_pFont;
	Texture2D* m_pTexture;
};

