#pragma once

#include <vector>
#include "../services/DatabaseService.h"
#include "../services/LauncherService.h"

class GameListView
{
public:
    // Store the pointers so we can use them later
    GameListView(DatabaseService* db, LauncherService* launcher);

    void Render();

private:
    DatabaseService* m_db;
    LauncherService* m_launcher;

    // Cache the games so we don't query SQL every single frame (60 times a second)
    std::vector<Game> m_gamesCache;
    bool m_needsRefresh = true;
};