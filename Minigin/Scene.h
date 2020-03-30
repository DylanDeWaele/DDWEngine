#pragma once
#include "SceneManager.h"

class SceneObject;
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
	void Add(SceneObject* object);

	void Update(float elapsedTime);
	void Render() const;
private:
	explicit Scene(const std::string& name);

	std::string m_Name;
	std::vector <SceneObject*> m_Objects{};

	static unsigned int m_IdCounter;
};