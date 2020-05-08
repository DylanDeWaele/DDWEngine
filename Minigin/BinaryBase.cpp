#include "MiniginPCH.h"
#include "BinaryBase.h"
#include <regex>
#include "Catch.hpp"

bool BinaryBase::SelectFile(const std::string& filename)
{
	//Find the extension .bin in the filename
	std::regex myRegex{ ".*?\\.(bin)" }; //Only filenames with the .bin extension are allowed

	if (std::regex_match(filename, myRegex)) //We use this regular expression to check the file name
	{
		m_Filename = filename;
		return true;
	}
	return false;
}
