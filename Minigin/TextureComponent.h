#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <string>
#include <memory>

class TextureComponent : public BaseComponent
{
public:
	//Ctor
	TextureComponent(const std::string& filename, float width, float height);

	//Dtor
	virtual ~TextureComponent();

	//Public member functions
	//Setters
	void SetTexture(const std::string& filename, float width = 0, float height = 0);
	void SetFlipped(bool flipped);

	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void Render() const override;

private:
	//Private datamembers
	Texture2D* m_pTexture;
	float m_Width;
	float m_Height;
	bool m_Flipped;
};
