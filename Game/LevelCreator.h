#pragma once
#include <vector>
#include "BinaryWriter.h"
#include "BinaryReader.h"

//Prefabs
#include "Box.h"
#include "Teleporter.h"
#include "LevelCounter.h"

#include "Scene.h"

class LevelCreator
{
public:
	struct Level
	{
	public:
		//Ctor
		Level() :levelCounter{0,0,0}, environment{}, teleporter{0,0,0,0,0,0} {};
		//Levelcounter
		LevelCounter levelCounter;
		//Environment -> boxes
		std::vector<Box> environment;
		//Teleporter
		Teleporter teleporter;
	};

	//Ctor
	LevelCreator() = default;

	//Dtor
	~LevelCreator() = default;

	void CreateLevels(); //Write all levels to a file
	void LoadLevel(int index, Scene* pScene); ////read the level from the file and add it to the scenemanager by index

private:
	//Private datamembers
	std::vector<Level> m_Levels;
	BinaryReader m_BinReader;
	BinaryWriter m_BinWriter;
	//Private functions
	//Levels
	void CreateLevel1(); //Put everything into place
	void CreateLevel2();
	void CreateLevel3();
	void ExportLevel(int index); //Write a level to a binary file
};