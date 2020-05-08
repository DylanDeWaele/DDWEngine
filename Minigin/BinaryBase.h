#pragma once
#include <string>

//Binary base class -> why? -> Select file function
class BinaryBase
{
public:
	//Ctor
	BinaryBase() = default;

	//Dtor
	virtual ~BinaryBase() = default;

	//Public member functions
	virtual bool SelectFile(const std::string& filename); //This returns a bool because only OBJ files can be read in

protected:
	std::string m_Filename;
};

