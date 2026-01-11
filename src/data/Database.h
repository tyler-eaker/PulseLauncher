#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "sqlite3.h"

namespace fs = std::filesystem;

struct Game 
{
	int id;
	std::string name;
	std::string path;
	int playtime; // In seconds
};

class Database 
{
public:
	Database(const std::string& dbPath);
	~Database();

	bool AddGame(const std::string& name, const std::string& path);

	Game GetGame(int id);
	std::vector<Game> GetAllGames();
	bool GameExists(const std::string& path);

	void DisplayGames();

	bool UpdateGameName(int gameId, std::string& newName);
	bool UpdateGamePath(int id, std::string& newPath);
	bool UpdateGamePlaytime(int gameId, int newDurationSeconds);

private:
	sqlite3* db;
	void Initialize();

	std::vector<Game> games;
};