#pragma once

#include "Window.h"
#include "Database.h"
#include "Launcher.h"

class Application 
{
public:
	Application();
	~Application();

	void Run();

private:
	Database* db = nullptr;

	std::string windowTitle = "Pulse Launcher";
	int windowSizeX = 1280;
	int windowSizeY = 720;

	Window window;
	
	std::string dbPath = "../../../../data/launcher.db";

	Launcher* launcher = nullptr;

	void Initialize();
	void Update();
	void Cleanup();
};