#pragma once
class GameObject;
class Font;

//The wrapper around our testscene
class TestScene
{
public:
	//Ctor
	TestScene();

	//Dtor
	~TestScene();

	//Public member functions
	void DeleteBackground();
private:
	//Private datamembers
	GameObject* m_pBackground;
	GameObject* m_pLogo;
	GameObject* m_pText;
	GameObject* m_pFPSCounter;
	Font* m_pFont;
	//Private functions
	void Initialize();
};

