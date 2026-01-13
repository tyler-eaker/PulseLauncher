#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Window.h"
#include "DatabaseService.h"
#include "LauncherService.h"
#include "UIManager.h"

#include <memory>

class Application
{
public:
	Application();
	~Application();

	// Helpers
	void Run();

private:
	// Core
	Window m_window;

	// Services
	std::unique_ptr<DatabaseService> m_db;
	std::unique_ptr<LauncherService> m_launcher;

	// UI
	std::unique_ptr<UIManager> m_ui;

	// Internal Helpers
	void Initialize();
	void Cleanup();
	void Update();
};