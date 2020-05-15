#pragma once
#include <Prefab.h>
class MainMenu : public Prefab
{
public:
	//Ctor
	MainMenu(const std::string& name = "MainMenu",
			 const std::string& tag = "MainMenu",
			 const std::string& collisionLayer = "Default");

	//Dtor
	virtual ~MainMenu() = default;
};

