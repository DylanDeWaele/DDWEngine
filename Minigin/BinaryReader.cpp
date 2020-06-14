#include "MiniginPCH.h"
#include "BinaryReader.h"

std::string BinaryReader::ReadString()
{
	std::string toRead{};

	if (m_InputStream.is_open())
	{
		//We read in the size, resize the string and read in the characters
		size_t stringSize{};
		m_InputStream.read((char*)& stringSize, sizeof(stringSize));
		toRead.resize(stringSize);
		m_InputStream.read((char*)& toRead[0], toRead.size());
	}
	return toRead;
}

void BinaryReader::Open()
{
	m_InputStream.open(m_Filename, std::ios::in | std::ios::binary);
}

void BinaryReader::Close()
{
	m_InputStream.close();
}
