#pragma once
#include "Singleton.h"

struct SDL_Window;
 
	class Minigin : public Singleton<Minigin>
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();

		//Setters
		void SetContinue(bool continueEngine);

		//Getters
		float GetWindowWidth() const;
		float GetWindowHeight() const;
		bool GetContinue() const;

	private:
		bool m_DoContinue;
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		const float m_Width = 640;
		const float m_Height = 480;
	};