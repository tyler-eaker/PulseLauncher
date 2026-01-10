#include <filesystem>
#include "Database.h"

int main() {
    // This will create "launcher.db" in your build folder
    Database db("../../../../data/launcher.db");

    // Add a dummy game
    std::cout << "Adding test game..." << std::endl;
    db.AddGame("Skyrim", "G:\\SteamLibrary\\steamapps\\common\\Skyrim Special Edition\\SkyrimSE.exe");

    // Read it back
    std::cout << "Reading games from DB..." << std::endl;
    std::vector<Game> games = db.GetAllGames();

    for (const auto& game : games) {
        std::cout << "Found: " << game.name << " | ID: " << game.id << std::endl;
    }

    return 0;
}