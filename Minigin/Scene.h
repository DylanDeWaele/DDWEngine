#pragma once
#include "SceneManager.h"

class GameObject;
class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	//Ctor
	Scene() = default;
	//Dtor
	~Scene();

	//Rule of 5
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	//Public member functions
	void Add(GameObject* object);
	void AddWhileRunning(GameObject* pObject);
	bool Remove(GameObject* pObject);

	void Initialize();
	void FixedUpdate();
	void Update();
	void Render() const;

	void CleanUp(); //Handles deletion of gameobjects after update calls

	//Getters
	const std::string& GetName() const;
	const std::vector<GameObject*>& GetObjects() const;
	GameObject* GetGameObjectWithTag(const std::string& tag) const;
	const std::vector<GameObject*> GetGameObjecstWithTag(const std::string& tag) const;

private:
	explicit Scene(const std::string& name);

	std::string m_Name;
	std::vector <GameObject*> m_Objects{};

	static unsigned int m_IdCounter;
};