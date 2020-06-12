#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>
#include "GameTime.h"

//UNIT TESTING
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"


using namespace std;
using namespace std::chrono;

void  Minigin::Initialize()
{
	//Initiliaze Catch
	Catch::Session().run();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		int(m_Width),
		int(m_Height),
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	//Seeding rand
	srand(unsigned int(time(nullptr)));
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
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		//Initialization
		sceneManager.Initialize();

		auto lastTime = std::chrono::high_resolution_clock::now();

		while (m_DoContinue)
		{
			//Changed the update loop to catch up in fixed steps
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = float(std::chrono::duration<float>(currentTime - lastTime).count());
			lastTime = currentTime;

			//Singleton for the elapsedTime
			GameTime::GetInstance().SetElapsedTime(min(deltaTime, 0.1f)); //Clip it when using breakpoints

			//Before handling input, first process the physics
			sceneManager.FixedUpdate();
			m_DoContinue = input.ProcessInput();
			sceneManager.Update();
			sceneManager.CleanUp();

			renderer.Render();
		}
	}

	Cleanup();
}

void Minigin::SetContinue(bool continueEngine)
{
	m_DoContinue = continueEngine;
}

float Minigin::GetWindowWidth() const
{
	return m_Width;
}

float Minigin::GetWindowHeight() const
{
	return m_Height;
}

bool Minigin::GetContinue() const
{
	return m_DoContinue;
}
