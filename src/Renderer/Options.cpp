#include "Options.h"





//Class GeneralOptions

GeneralOptions* GeneralOptions::s_generalOptions = nullptr;

//Operations from and in file
void GeneralOptions::readFromFile(const std::string& fileName)
{
	s_generalOptions->m_fps = 60;
	s_generalOptions->m_fileName = fileName;
	std::vector<std::string> lines = getlines(fileName);

	for (int i = 0; i < lines.size(); i++)
	{
		std::string& line = lines[i];
		if (!isCommentLine(line))
		{
			if (line.find("tileDimension=(") != -1)
			{
				line = stride(line, "tileDimension=(");
				line = remove(line, ")");
				std::vector<std::string> str = split(line, ",");

				s_generalOptions->m_tileWidth = std::stoi(str[0]);
				s_generalOptions->m_tileHeight = std::stoi(str[1]);
			}
		}
	}
}

void GeneralOptions::writeInFile()
{

}
//Operations from and in file

//Class GeneralOptions

