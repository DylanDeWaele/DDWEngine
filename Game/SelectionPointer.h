#pragma once

#include "Prefab.h"

class SelectionPointer : public Prefab
{
public:
	//Ctor
	SelectionPointer(float x, float y, const std::string& name = "SelectionPointer",
									   const std::string& tag = "SelectionPointer",
									   const std::string& collisionLayer = "Default");

	//Dtor
	virtual ~SelectionPointer() = default;
};

