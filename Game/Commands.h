#pragma once
#include "Command.h" //BASE CLASS

class LeftCommand : public Command
{
public:
	//Ctor
	LeftCommand() = default;
	//Dtor
	virtual ~LeftCommand() = default;
	//Public member functions
	virtual void Execute() override;
};

class RightCommand : public Command
{
public:
	//Ctor
	RightCommand() = default;
	//Dtor
	virtual ~RightCommand() = default;
	//Public member functions
	virtual void Execute() override;
};

class Action1Command : public Command
{
public:
	//Ctor
	Action1Command() = default;
	//Dtor
	virtual ~Action1Command() = default;
	//Public member functions
	virtual void Execute() override;
};

class Action2Command : public Command
{
public:
	//Ctor
	Action2Command() = default;
	//Dtor
	virtual ~Action2Command() = default;
	//Public member functions
	virtual void Execute() override;
};

class UpCommand : public Command
{
public:
	//Ctor
	UpCommand() = default;
	//Dtor
	virtual ~UpCommand() = default;
	//Public member functions
	virtual void Execute() override;
};

class DownCommand : public Command
{
public:
	//Ctor
	DownCommand() = default;
	//Dtor
	virtual ~DownCommand() = default;
	//Public member functions
	virtual void Execute() override;
};