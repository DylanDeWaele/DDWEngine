#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "FpsCounterComponent.h"

using namespace std;
using namespace std::chrono;

void  Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void  Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Font that we will use for texts
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent{ {0,0,0} });
	go->AddComponent(new TextureComponent{ "background.jpg" });
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent{ {216,180,0} });
	go->AddComponent(new TextureComponent{ "logo.png" });
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent{ {80, 20,0} });
	go->AddComponent(new TextComponent{ "Programming 4 Assignment", font });
	scene.Add(go);

	auto fpsCounter = std::make_shared<GameObject>();
	fpsCounter->AddComponent(new TransformComponent{ {0,0,0} });
	fpsCounter->AddComponent(new TextComponent{ "00", font });
	fpsCounter->AddComponent(new FpsCounterComponent{});
	scene.Add(fpsCounter);
}

void  Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void  Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;

		while (doContinue)
		{
			//Changed the update loop to catch up in fixed steps
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = float(std::chrono::duration_cast<milliseconds>(currentTime - lastTime).count());
			lastTime = currentTime;
			lag += deltaTime;

			doContinue = input.ProcessInput();
			while (lag >= MsPerFrame)
			{
				sceneManager.Update(deltaTime);
				lag -= MsPerFrame;
			}
			renderer.Render();
		}
	}

	Cleanup();
}
