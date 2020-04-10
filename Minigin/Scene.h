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

	void Initialize();
	void FixedUpdate();
	void Update();
	void Render() const;

	//Getters
	const std::string& GetName() const;
	const std::vector<GameObject*>& GetObjects() const;

private:
	explicit Scene(const std::string& name);

	std::string m_Name;
	std::vector <GameObject*> m_Objects{};

	static unsigned int m_IdCounter;
};