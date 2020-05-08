#pragma once
//Unit testing includes
#include "Catch.hpp"

//Inheritance includes
#include "BinaryBase.h"

//Includes
#include <fstream>

//Binary writer class -> write objects to binary file
class BinaryWriter : public BinaryBase
{
public: 
	//Ctor
	BinaryWriter() = default;
	
	//Dtor
	virtual ~BinaryWriter() = default;
	
	//Public member functions
	void Open();
	void Close();

	template <typename T>
	void WriteData(const T& data);

	void WriteString(const std::string string);

private:
	//Private datamembers
	std::ofstream m_OutputStream;
};

#pragma region TEMPLATE FUNCTIONS
template<typename T>
void BinaryWriter::WriteData(const T& data)
{
	if (m_OutputStream.is_open()) //If the file was opened correctly
	{
		m_OutputStream.write((const char*)& data, sizeof(data)); //Write the data to the file
	}
}
#pragma endregion
