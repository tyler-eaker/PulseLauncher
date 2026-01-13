#pragma once

#include "tinyfiledialogs.h"
#include "DatabaseService.h"
#include "GameListView.h"
#include "imgui.h"

class AddGamePopup
{
public:
	AddGamePopup(DatabaseService* db, GameListView* gameListView);
	
	// Helpers
	void Render();

private:
	// Service Dependencies
	DatabaseService* m_db;

	// UI Dependencies
	GameListView* m_gameListView;
};