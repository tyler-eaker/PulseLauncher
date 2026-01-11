#pragma once

#include <string>
#include <vector>

class Launcher
{
public:
	long long LaunchGame(const std::string& exePath);

private:
#ifdef _WIN32
	std::wstring StringToWide(const std::string& str);
#endif
};