#include "GamePCH.h"
#include "MainMenu.h"

//Prefab
#include "Text.h"
#include "SelectionPointer.h"

//Components
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "MainMenuComponent.h"

#include "ResourceManager.h"

MainMenu::MainMenu(const std::string& name, const std::string& tag, const std::string& collisionLayer)
	:Prefab{ name, tag, collisionLayer }
{
	const float& windowWidth{ Minigin::GetInstance().GetWindowWidth() };
	const float& windowHeight{ Minigin::GetInstance().GetWindowHeight() };
	const float xOffset = 100.f;
	const float yOffset = 75.f;
	const float textX = windowWidth / 2.f - xOffset;
	float textY = windowHeight - yOffset;
	const unsigned int fontsize = 30;

	//1st Child -> IntroScreen
	GameObject* pIntroScreen = new GameObject{"IntroScreen", "IntroScreen"};
	pIntroScreen->AddComponent(new TransformComponent{ {0,windowHeight} });
	pIntroScreen->AddComponent(new TextureComponent{ "TitleScreen.png",windowWidth,windowHeight });
	m_pGameObject->AddChild(pIntroScreen);

	//2nd Screen -> Selection screen
	GameObject* pSelectionScreen = new GameObject{"SelectionScreen", "SelectionScreen"};

	//1 Title
	Text title = Text{ textX, textY, "BUBBLE BOBBLE",ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	textY -= yOffset;
	//2 Selection pointer
	const float selectionPointerXOffset = 50.f;
	SelectionPointer selectionPointer = SelectionPointer{ textX - selectionPointerXOffset, textY };
	//3. 1P start text
	Text onePlayerStartText = Text{ textX, textY, "1P START",ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	textY -= yOffset;
	//4. 2P start text
	Text twoPlayerStartText = Text{ textX, textY, "2P START",ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	textY -= yOffset;
	//5. Versus start text
	Text vsStartText = Text{ textX, textY, "VS START",ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	textY -= yOffset;
	//6. Quit text
	Text quitText = Text{ textX, textY, "QUIT",ResourceManager::GetInstance().LoadFont("Lingua.otf", fontsize) };
	
	//Add everything to selection screen
	pSelectionScreen->AddChild(title.GetGameObject());
	pSelectionScreen->AddChild(selectionPointer.GetGameObject());
	pSelectionScreen->AddChild(onePlayerStartText.GetGameObject());
	pSelectionScreen->AddChild(twoPlayerStartText.GetGameObject());
	pSelectionScreen->AddChild(vsStartText.GetGameObject());
	pSelectionScreen->AddChild(quitText.GetGameObject());

	//Add selection screen to gameobject
	m_pGameObject->AddChild(pSelectionScreen);
	//Add main menu component
	m_pGameObject->AddComponent(new MainMenuComponent{});
}
