#pragma once
#include <BaseComponent.h>

class MainMenuComponent : public BaseComponent
{
public:
	//Ctor
	MainMenuComponent();
	//Dtor
	virtual ~MainMenuComponent() = default;

	//Public member functions
	virtual void Initialize() override;
	virtual void Update() override;

	void SelectUp();
	void SelectDown();
	void Select();

private:
	//Private datamembers
	//Intro screen
	GameObject* m_pIntroScreen;
	const float m_IntroTime;
	float m_CurrentTime;

	//Selection screen
	int m_CurrentOption;
	const float m_SelectionPointerXOffset;
	GameObject* m_pSelectionPointer;
	GameObject* m_pSelectionScreen;
	std::vector<GameObject*> m_pOptions;

	//Private functions
	void UpdateIntroScreen();
	void SetSelectionPointerToOption(int optionIndex);
};

