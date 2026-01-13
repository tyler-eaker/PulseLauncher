#pragma once

#include "tinyfiledialogs.h"
#include "DatabaseService.h"
#include "LauncherService.h"
#include "imgui.h"

class AddGamePopup
{
public:
	AddGamePopup(DatabaseService* db);
	
	void Render();

private:
	DatabaseService* m_db;

};