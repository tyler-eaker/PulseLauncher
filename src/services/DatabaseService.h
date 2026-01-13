#pragma once

#include "Game.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "sqlite3.h"

namespace fs = std::filesystem;

class DatabaseService
{
public:
	DatabaseService(const std::string& path);
	~DatabaseService();

	// Verifiers
	bool GameExists(const std::string& path);

	// Getters
	Game GetGame(int id);
	std::vector<Game> GetAllGames();

	// Setters
	bool AddGame(const std::string& name, const std::string& path);
	bool UpdateGameName(int gameId, std::string& newName);
	bool UpdateGamePath(int id, std::string& newPath);
	bool UpdateGamePlaytime(int gameId, int newDurationSeconds);

private:
	// Database
	sqlite3* m_db;
	std::vector<Game> m_games;

	// Local Variables
	std::string m_path;

	// Internal Helpers
	void Initialize();
	void Cleanup();
};