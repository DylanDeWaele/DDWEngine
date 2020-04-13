#pragma once
#include "Command.h" //BASE CLASS

class MoveLeftCommand : public Command
{
public:
	//Ctor
	MoveLeftCommand() = default;
	//Dtor
	virtual ~MoveLeftCommand() = default;
	//Public member functions
	virtual void Execute() override;
};

class MoveRightCommand : public Command
{
public:
	//Ctor
	MoveRightCommand() = default;
	//Dtor
	virtual ~MoveRightCommand() = default;
	//Public member functions
	virtual void Execute() override;
};

class JumpCommand : public Command
{
public:
	//Ctor
	JumpCommand() = default;
	//Dtor
	virtual ~JumpCommand() = default;
	//Public member functions
	virtual void Execute() override;
};

class ShootCommand : public Command
{
public:
	//Ctor
	ShootCommand() = default;
	//Dtor
	virtual ~ShootCommand() = default;
	//Public member functions
	virtual void Execute() override;
};

