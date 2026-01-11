#pragma once

#include "Database.h"
#include "Launcher.h"

class Application 
{
public:
	Application();
	~Application();

	void Run();

private:
	const std::string name = "Pulse Launcher";

	Database* db = nullptr;
	std::string dbPath = "../../../../data/launcher.db";

	Launcher* launcher = nullptr;

	void Initialize();
	void Update();
	void Cleanup();
};