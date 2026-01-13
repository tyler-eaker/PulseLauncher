#pragma once

#include "DatabaseService.h"
#include "LauncherService.h"
#include "imgui.h"

#include <vector>
#include <string>

class GameListView
{
public:
    GameListView(DatabaseService* db, LauncherService* launcher);

    void Render();

private:
    DatabaseService* m_db;
    LauncherService* m_launcher;

    std::vector<Game> m_gamesCache;
    bool m_needsRefresh = true;
};