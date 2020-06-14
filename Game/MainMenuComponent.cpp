#include "GamePCH.h"
#include "MainMenuComponent.h"

#include "GameTime.h"
#include "GameMode.h"
#include "SceneManager.h"
#include "Scene.h"

//Components
#include "TransformComponent.h"
#include "ScoreComponent.h"
#include "SoundComponent.h"

MainMenuComponent::MainMenuComponent()
	:BaseComponent{},
	m_IntroTime{ 3.f }, //3 seconds
	m_CurrentTime{ 0 },
	m_pIntroScreen{ nullptr },
	m_pSelectionScreen{ nullptr },
	m_pSelectionPointer{ nullptr },
	m_pOptions{},
	m_SelectionPointerXOffset{ 50.f },
	m_CurrentOption{ 0 }
{
}

void MainMenuComponent::Initialize()
{
	m_pIntroScreen = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("IntroScreen");
	m_pSelectionScreen = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("SelectionScreen");

	if (m_pOptions.empty())
	{
		m_pOptions.push_back(m_pSelectionScreen->GetChild(2)); //1P START
		m_pOptions.push_back(m_pSelectionScreen->GetChild(3)); //2P START
		m_pOptions.push_back(m_pSelectionScreen->GetChild(4)); //VS Start
		m_pOptions.push_back(m_pSelectionScreen->GetChild(5)); //QUIT
	}

	m_pIntroScreen->SetActive(true);
	m_pSelectionScreen->SetActive(false);
	m_CurrentTime = 0;

	//Put the selection pointer at the first selection position
	m_pSelectionPointer = SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("SelectionPointer");
	m_CurrentOption = 0;
	SetSelectionPointerToOption(m_CurrentOption);
}

void MainMenuComponent::Update()
{
	//Introscreen
	if (m_pIntroScreen->IsActive())
		UpdateIntroScreen();
}

void MainMenuComponent::SelectUp()
{
	if (!m_pIntroScreen->IsActive())
	{
		m_CurrentOption--;
		if (m_CurrentOption < 0)
			m_CurrentOption = int(m_pOptions.size()) - 1;

		SetSelectionPointerToOption(m_CurrentOption);
	}
}

void MainMenuComponent::SelectDown()
{
	if (!m_pIntroScreen->IsActive())
	{
		m_CurrentOption++;
		if (m_CurrentOption > int(m_pOptions.size()) - 1)
			m_CurrentOption = 0;

		SetSelectionPointerToOption(m_CurrentOption);
	}
}

void MainMenuComponent::Select()
{
	if (!m_pIntroScreen->IsActive())
	{
		switch (m_CurrentOption)
		{
		case 0:
			//Load singeplayer
			GameMode::GetInstance().SetGameMode(GameMode::Mode::Singleplayer);
			SceneManager::GetInstance().SetActiveScene("Level1SP");
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->Reset();
			break;
		case 1:
			//Load 2 player
			GameMode::GetInstance().SetGameMode(GameMode::Mode::Coop);
			SceneManager::GetInstance().SetActiveScene("Level1MP");
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->Reset();
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<ScoreComponent>()->Reset();
			break;
		case 2:
			//Load versus
			GameMode::GetInstance().SetGameMode(GameMode::Mode::Versus);
			SceneManager::GetInstance().SetActiveScene("Level1VS");
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player")->GetComponent<ScoreComponent>()->Reset();
			SceneManager::GetInstance().GetActiveScene()->GetGameObjectWithTag("Player2")->GetComponent<ScoreComponent>()->Reset();
			break;
		case 3:
			//Quit game
			Minigin::GetInstance().SetContinue(false);
			break;
		}
	}
}

void MainMenuComponent::UpdateIntroScreen()
{
	m_CurrentTime += GameTime::GetInstance().GetElapsedTime();

	if (m_CurrentTime > m_IntroTime)
	{
		m_pIntroScreen->SetActive(false);
		m_pSelectionScreen->SetActive(true);
	}
}

void MainMenuComponent::SetSelectionPointerToOption(int optionIndex)
{
	const glm::vec2& firstOptionPosition = m_pOptions[optionIndex]->GetComponent<TransformComponent>()->GetPosition();
	m_pSelectionPointer->GetComponent<TransformComponent>()->SetPosition({ firstOptionPosition.x - m_SelectionPointerXOffset, firstOptionPosition.y });
}
