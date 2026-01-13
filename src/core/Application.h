#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Window.h"

#include "DatabaseService.h"
#include "LauncherService.h"

#include "UIManager.h"

class Application
{
public:
	Application();
	~Application();

	// Helpers
	void Run();

private:
	// Local Variables
	std::string m_dbPath = "../../../../data/launcher.db";

	// Core
	Window m_window;

	// Services
	DatabaseService m_db;
	LauncherService m_launcher;

	// UI
	UIManager m_ui;

	// Internal Helpers
	void Initialize();
	void Cleanup();
	void Update();
};