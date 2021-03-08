#pragma once

#include "PrecompiledHeaders.h"
#include "AddonsString.h"

class GeneralOptions
{
public:
	GeneralOptions() {}

	static void readFromFile(const std::string& fileName);
	static void writeInFile();

	static void setFileName(const std::string& fileName) { s_generalOptions->m_fileName = fileName; }
	static void setFps(uint32_t fps) { s_generalOptions->m_fps = fps; }
	static void setTileWidht(uint32_t tileWidth) { s_generalOptions->m_tileWidth = tileWidth; }
	static void setTileHeight(uint32_t tileHeight) { s_generalOptions->m_tileHeight = tileHeight; }
	static void setLevelWidth(uint32_t levelWidth) { s_generalOptions->m_levelWidth = levelWidth; }
	static void setLevelHeight(uint32_t levelHeight) { s_generalOptions->m_levelHeight = levelHeight; }
	static void setBaseFilePath(const std::string& baseFilePath) { s_generalOptions->m_baseFilePath = baseFilePath; }
	static void setLevelFilePath(const std::string& levelFilePath) { s_generalOptions->m_levelFilePath = levelFilePath; }

	static std::string getFileName() { return s_generalOptions->m_fileName; }
	static uint32_t getFps() { return s_generalOptions->m_fps; }
	static uint32_t getTileWidht() { return s_generalOptions->m_tileWidth; }
	static uint32_t getTileHeight() { return s_generalOptions->m_tileHeight; }
	static uint32_t getLevelWidth() { return s_generalOptions->m_levelWidth; }
	static uint32_t getLevelHeight() { return s_generalOptions->m_levelHeight; }
	static std::string getBaseFilePath() { return s_generalOptions->m_baseFilePath; }
	static std::string getLevelFilePath() { return s_generalOptions->m_levelFilePath; }

	static GeneralOptions* s_generalOptions;

private:
	uint32_t m_fps;
	uint32_t m_tileWidth, m_tileHeight;
	uint32_t m_levelWidth, m_levelHeight;

	std::string m_fileName;

	std::string m_baseFilePath;
	std::string m_levelFilePath;
};