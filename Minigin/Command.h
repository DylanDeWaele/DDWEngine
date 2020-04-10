#pragma once
class GameObject;

class Command
{
public:
	//Ctor
	Command() = default;
	//Dtor
	virtual ~Command() = default;
	//Public member functions
	virtual void Execute() = 0;
};

