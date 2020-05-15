#include "GamePCH.h"
#include "LevelCreator.h"

//Scene
#include "SceneManager.h"
#include "Scene.h"

//Components
#include "TransformComponent.h"
#include "BoxColliderComponent.h"

void LevelCreator::LoadLevel(int index, Scene* pScene)
{
	m_BinReader.SelectFile("../Data/Level_" + std::to_string(index + 1) + ".bin");
	m_BinReader.Open();
	//1. Read the lvlcounter from a file
	float x, y;
	int levelCounter;
	//Read x
	m_BinReader.ReadData(x);
	//Read y
	m_BinReader.ReadData(y);
	//Read levelcounter
	m_BinReader.ReadData(levelCounter);
	//Create levelCounter
	LevelCounter lvlCounter = LevelCounter{ x,y,levelCounter };
	////2. Read the teleporter from a file
	float width, height, tpX, tpY;
	//Read x
	m_BinReader.ReadData(x);
	//Read y
	m_BinReader.ReadData(y);
	//Read width
	m_BinReader.ReadData(width);
	//Read height
	m_BinReader.ReadData(height);
	//Read tpX
	m_BinReader.ReadData(tpX);
	//Read tpy
	m_BinReader.ReadData(tpY);
	//Create teleporter
	Teleporter teleporter = Teleporter{ x,y,width,height,tpX,tpY };
	//3. Read the amount of boxes from a file
	size_t size;
	m_BinReader.ReadData(size);
	std::vector<Box> boxes{};
	//4. For all these boxes, read them in
	for (size_t i = 0; i < size; i++)
	{
		std::string name, tag, collision;
		//Read 
		m_BinReader.ReadData(x);
		//Read y
		m_BinReader.ReadData(y);
		//Read width
		m_BinReader.ReadData(width);
		//Read height
		m_BinReader.ReadData(height);
		//Read name
		name = m_BinReader.ReadString();
		//Read tag
		tag = m_BinReader.ReadString();
		//Read collisionLayer
		collision = m_BinReader.ReadString();
		//Create box
		Box box = Box{ x,y,width,height,name,tag,collision };
		boxes.push_back(box);
	}
	m_BinReader.Close();

	//Add to scene
	//Add lvlcounter
	pScene->Add(lvlCounter.GetGameObject());
	//Add teleporter
	pScene->Add(teleporter.GetGameObject());
	//Add all the boxes
	for (size_t i = 0; i < size; i++)
	{
		pScene->Add(boxes[i].GetGameObject());
	}
}

void LevelCreator::CreateLevels()
{
	CreateLevel1();
}

void LevelCreator::CreateLevel1()
{
	const float windowWidth{ Minigin::GetInstance().GetWindowWidth() };
	const float windowHeight{ Minigin::GetInstance().GetWindowHeight() };
	const float thickness{ 20.f };

	Level level1{};

	level1.levelCounter = LevelCounter{ 305, windowHeight - thickness - 7, 01 };
	level1.teleporter = Teleporter{ 0, -30,windowWidth, 10, 305, windowHeight };
	
	//Initialize ground 1
	Box box = Box{ 0,thickness, windowWidth / 3.f, thickness, "Ground", "Ground" };
	level1.environment.push_back(box);
	box = Box{ 2 * windowWidth / 3.f,thickness, windowWidth / 3.f, thickness, "Ground", "Ground" };
	level1.environment.push_back(box);
	box = Box{ 272.5, thickness, 100.f,thickness, "Ground", "Ground" };
	level1.environment.push_back(box);

	//Initialize walls
	box = Box{ 0, windowHeight, 30, windowHeight, "Left Wall" };
	level1.environment.push_back(box);
	box = Box{ windowWidth - 30, windowHeight, 30, windowHeight, "Right Wall" };
	level1.environment.push_back(box);
	
	//Platform
	box = Box{ 150, 120, 350, thickness, "Platform", "Default", "Platform" };
	level1.environment.push_back(box);
	box = Box{ 150, 220, 350, thickness, "Platform", "Default", "Platform" };
	level1.environment.push_back(box);
	box = Box{ 150, 320, 350, thickness, "Platform", "Default", "Platform" };
	level1.environment.push_back(box);
	
	//Ceiling
	box = Box{ 0,windowHeight - thickness * 1.5f, 300, thickness, "Ground", "Ground" };
	level1.environment.push_back(box);
	box = Box{ 340 ,windowHeight - thickness * 1.5f, 300, thickness, "Ground", "Ground" };
	level1.environment.push_back(box);

	m_Levels.push_back(level1);

	ExportLevel(0);
}

void LevelCreator::ExportLevel(int index)
{
	m_BinWriter.SelectFile("../Data/Level_" + std::to_string(index + 1) + ".bin"); //Create level 1 file
	m_BinWriter.Open();
	//1. Write levelcounter + requirements to file
	const glm::vec2& levelCountPos = m_Levels[index].levelCounter.GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
	//write x
	m_BinWriter.WriteData(levelCountPos.x);
	//write y
	m_BinWriter.WriteData(levelCountPos.y);
	//write count
	m_BinWriter.WriteData(index + 1);
	//2. Write teleporter + requirements to file
	const glm::vec2& teleporterPos = m_Levels[index].teleporter.GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
	float width = m_Levels[index].teleporter.GetGameObject()->GetComponent<BoxColliderComponent>()->GetRect().width;
	float height = m_Levels[index].teleporter.GetGameObject()->GetComponent<BoxColliderComponent>()->GetRect().height;
	const glm::vec2& teleportPos = m_Levels[index].teleporter.GetGameObject()->GetChild(0)->GetComponent<TransformComponent>()->GetPosition();
	//Write x
	m_BinWriter.WriteData(teleporterPos.x);
	//Write y
	m_BinWriter.WriteData(teleporterPos.y);
	//Write width
	m_BinWriter.WriteData(width);
	//Write height
	m_BinWriter.WriteData(height);
	//Write tpX
	m_BinWriter.WriteData(teleportPos.x);
	//Write tpY
	m_BinWriter.WriteData(teleportPos.y);
	//3. Write amount of boxes to file
	const size_t size = m_Levels[index].environment.size();
	m_BinWriter.WriteData(size);
	//4. Write all boxes + requirements to file
	for (size_t i = 0; i < size; i++)
	{
		const Box& box = m_Levels[index].environment[i];
		const glm::vec2& position = box.GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
		float width = box.GetGameObject()->GetComponent<BoxColliderComponent>()->GetRect().width;
		float height = box.GetGameObject()->GetComponent<BoxColliderComponent>()->GetRect().height;
		const std::string& name = box.GetGameObject()->GetName();
		const std::string& tag = box.GetGameObject()->GetTag();
		const std::string& collisionLayer = box.GetGameObject()->GetCollisionLayer();
		//Write x
		m_BinWriter.WriteData(position.x);
		//Write y
		m_BinWriter.WriteData(position.y);
		//Write width
		m_BinWriter.WriteData(width);
		//Write height
		m_BinWriter.WriteData(height);
		//Write name
		m_BinWriter.WriteString(name);
		//Write tag
		m_BinWriter.WriteString(tag);
		//Write collisionLayer
		m_BinWriter.WriteString(collisionLayer);
	}
	m_BinWriter.Close();
}
