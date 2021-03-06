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

	void CleanUp(); //Handles deletion of objects after the update loop is finished

	//Setters
	void SetActiveScene(const std::string& sceneName);
	//Getters
	Scene* GetActiveScene() const;
	Scene* GetSceneByName(const std::string& name) const;
	Scene* GetPreviousScene() const;

private:
	friend class Singleton<SceneManager>;
	std::vector<Scene*> m_Scenes;
	Scene* m_pActiveScene;
	Scene* m_pPreviousScene;

	bool m_SkipScene = false; //This boolean determines whether we should skip updating all the components/gameobjects in a scene (scene transition)
};

