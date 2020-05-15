#pragma once
#include "GamePCH.h"
#include <BaseComponent.h>

class GameOverScreenComponent : public BaseComponent
{
public:
	//Ctor
	GameOverScreenComponent();
	//Dtor
	virtual ~GameOverScreenComponent() = default;

	//Public member functions
	virtual void Initialize() override;
	virtual void Update() override;

	void SelectUp();
	void SelectDown();
	void Select();

private:
	//Private datamembers
	//Selection
	int m_CurrentOption;
	const float m_SelectionPointerXOffset;
	GameObject* m_pSelectionPointer;
	std::vector<GameObject*> m_pOptions;

	//Private functions
	void SetSelectionPointerToOption(int optionIndex);
};