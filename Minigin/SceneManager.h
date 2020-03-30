#pragma once
#include "Singleton.h"

	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		//Dtor
		~SceneManager();

		Scene& CreateScene(const std::string& name);

		void Update(float elapsedTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_Scenes;
	};

