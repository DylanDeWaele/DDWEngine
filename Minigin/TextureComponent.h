#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <string>
#include <memory>

class TextureComponent : public BaseComponent
{
public:
	//Ctor
	TextureComponent(const std::string& filename);

	//Dtor
	virtual ~TextureComponent() = default;

	//Public member functions
	//Setters
	void SetTexture(const std::string& filename);

	virtual void Update(float elapsedTime) override;
	virtual void Render() const override;

private:
	//Private datamembers
	std::shared_ptr<Texture2D> m_pTexture;
};
