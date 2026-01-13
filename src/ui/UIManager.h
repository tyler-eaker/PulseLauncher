#pragma once

#include "AddGamePopup.h"
#include "GameListView.h"
#include "MainLayout.h"

struct GLFWwindow;

class UIManager
{
public:
	UIManager(GLFWwindow* window, DatabaseService* db, LauncherService* launcher);
	~UIManager();

	void Render();

private:
	std::string m_fontPath = "../../../../resources/DMSans.ttf";

	MainLayout m_mainLayout;
	GameListView m_gameListView;
	AddGamePopup m_addGamePopup;

	void Initialize(GLFWwindow* window);
	void Cleanup();
};