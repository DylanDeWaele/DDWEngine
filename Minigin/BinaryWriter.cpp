#include "MiniginPCH.h"
#include "BinaryWriter.h"

void BinaryWriter::Open()
{
	m_OutputStream.open(m_Filename, std::ios::out | std::ios::binary);
}

void BinaryWriter::Close()
{
	m_OutputStream.close();
}

void BinaryWriter::WriteString(const std::string string)
{
	if (m_OutputStream.is_open())
	{
		//When writing a string we first want to write its size
		size_t stringSize{ static_cast<size_t>(string.size()) };
		m_OutputStream.write((const char*)& stringSize, sizeof(stringSize));
		m_OutputStream.write(string.c_str(), string.size());
	}
}
