#include "Application.h"

int main() 
{
    Application app;
    app.Run();

    // This will create "launcher.db" in your build folder
    Database db("../../../../data/launcher.db");

    // Add a dummy game
    db.AddGame("GH3", "G:\\Games\\Guitar Hero III\\GH3.exe");

    // Read it back
    std::cout << "Reading games from DB..." << std::endl;
    
    db.DisplayGames();

    return 0;
}