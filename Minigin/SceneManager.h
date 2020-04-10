#pragma once
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	//Ctor
	SceneManager();

	//Dtor
	~SceneManager();

	Scene& CreateScene(const std::string& name);

	void Initialize(); //This is like the start function in unity
	void FixedUpdate(); //Do physics handling here
	void Update();
	void Render();

	//Setters
	void SetActiveScene(const std::string& sceneName);
	//Getters
	Scene* GetActiveScene() const;

private:
	friend class Singleton<SceneManager>;
	std::vector<Scene*> m_Scenes;
	Scene* m_pActiveScene;
};

