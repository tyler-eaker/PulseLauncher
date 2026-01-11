#pragma once

#include "GUI.h"
#include "Database.h"
#include "Launcher.h"

class Application 
{
public:
	Application();
	~Application();

	void Run();

private:
    std::string windowTitle = "Pulse Launcher";
    int windowSizeX = 1280;
    int windowSizeY = 720;
    std::string dbPath = "../../../../data/launcher.db";

    Database db;
    Window window;
    GUI gui;

    Launcher* launcher = nullptr;

    void Initialize();
    void Update();
    void Cleanup();
};