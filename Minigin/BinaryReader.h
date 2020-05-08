#pragma once
//Unit testing includes
#include "Catch.hpp"

//Inheritance includes
#include "BinaryBase.h"

//Includes
#include <vector>
#include "Structs.h"
#include <fstream>


//Binary reader class -> read objects in from binary file
class BinaryReader : public BinaryBase
{
public:
	//Ctor
	BinaryReader() = default;

	//Dtor
	virtual ~BinaryReader() = default;

	//Public member functions
	void Open();
	void Close();

	std::string ReadString();

	template<typename T>
	void ReadData(T& data);
private:
	//Private datamembers
	std::ifstream m_InputStream;
};

#pragma region TEMPLATE FUNCTIONS
template<typename T>
inline void BinaryReader::ReadData(T& data)
{
	if (m_InputStream.is_open())
	{
		//We read in the data
		m_InputStream.read((char*)& data, sizeof(data));
	}
}
#pragma endregion
