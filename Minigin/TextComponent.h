#pragma once
#include "BaseComponent.h"
#include <string>
class Font;
class Texture2D;

class TextComponent final : public BaseComponent
{
public:
	//Ctor
	TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
	
	//Dtor
	virtual ~TextComponent() = default;

	//Public member functions	
	//Setters
	void SetText(const std::string& text);

	virtual void Update(float elapsedTime) override;
	virtual void Render() const override;

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture2D> m_Texture;
};

