#pragma once

#include <string>

struct Game
{
	int id = -1;
	std::string name;
	std::string path;
	int playtime = 0; // In seconds
};