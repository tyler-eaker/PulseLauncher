#include "Database.h"

Database::Database(const std::string& dbPath)
{
    // Open the database connection
    int exit = sqlite3_open(dbPath.c_str(), &db);

    if (exit != SQLITE_OK) 
    {
        std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << '\n';
    }
    else 
    {
        std::cout << "Database opened successfully!\n";
        Initialize();
    }
}

Database::~Database()
{
    if (db) 
    { 
        sqlite3_close(db);
    };
}

void Database::Initialize()
{
    // Create the table if it doesn't exist
    std::string sql =
        "CREATE TABLE IF NOT EXISTS GAMES("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "NAME           TEXT    NOT NULL, "
        "PATH           TEXT    NOT NULL, "
        "PLAYTIME       INT     DEFAULT 0);";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) 
    {
        std::cerr << "Error Creating Table: " << messageError << '\n';
        sqlite3_free(messageError);
    }
    else 
    {
        std::cout << "Table initialized.\n";
    }

    this->games = GetAllGames();
}

bool Database::AddGame(const std::string& name, const std::string& path)
{
    if (!fs::exists(path)) 
    {
        std::cerr << "ERROR: " << path << " is an invalid filepath." << '\n';
        return false;
    }

    if (GameExists(path)) 
    {
        std::cout << "Game already exists in database: " << name << '\n';
        return false;
    }

    std::cout << "Adding game: " << name << '(' << path << ")\n";

    std::string sql = "INSERT INTO GAMES (NAME, PATH) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) 
    {
        return false;
    }

    // Bind parameters in order of the "?"
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, path.c_str(), -1, SQLITE_TRANSIENT);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (result == SQLITE_DONE);
}

Game Database::GetGame(int id)
{
    Game game = {}; // Empty game object
    game.id = -1;   // Flag to indicate "not found"

    std::string sql = "SELECT * FROM GAMES WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << '\n';
        return game;
    }

    sqlite3_bind_int(stmt, 1, id);

    // Executes if the game ID is valid
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        game.id = sqlite3_column_int(stmt, 0);

        const unsigned char* name = sqlite3_column_text(stmt, 1);
        const unsigned char* path = sqlite3_column_text(stmt, 2);

        game.name = name ? reinterpret_cast<const char*>(name) : "";
        game.path = path ? reinterpret_cast<const char*>(path) : "";
        game.playtime = sqlite3_column_int(stmt, 3);
    }

    sqlite3_finalize(stmt);
    return game;
}

// Helper callback for fetching data
static int callback(void* data, int argc, char** argv, char** azColName)
{
    auto* games = static_cast<std::vector<Game>*>(data);
    Game g;
    // argv[0] is ID, argv[1] is NAME, argv[2] is PATH... based on query order
    g.id = std::stoi(argv[0]);
    g.name = argv[1] ? argv[1] : "Unknown";
    g.path = argv[2] ? argv[2] : "";
    g.playtime = argv[3] ? std::stoi(argv[3]) : 0;

    games->push_back(g);
    return 0;
}

std::vector<Game> Database::GetAllGames()
{
    std::vector<Game> games;
    const char* sql = "SELECT * FROM GAMES;";

    // We pass &games as the "data" argument so the callback can fill it
    sqlite3_exec(db, sql, callback, &games, NULL);

    return games;
}

bool Database::GameExists(const std::string& path) 
{
    std::string sql = "SELECT 1 FROM GAMES WHERE PATH = ? LIMIT 1;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) 
    {
        std::cerr << "Error checking existence: " << sqlite3_errmsg(db) << '\n';
        return false;
    }

    sqlite3_bind_text(stmt, 1, path.c_str(), -1, SQLITE_TRANSIENT);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return (result == SQLITE_ROW);
}

void Database::DisplayGames()
{
    for (const auto& game : games)
    {
        std::cout << "Found: " << game.name << " | ID: " << game.id << '\n';
    }
}

bool Database::UpdateGameName(int id, std::string& newName)
{
    std::string sql = "UPDATE GAMES SET NAME = ? WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Error preparing update: " << sqlite3_errmsg(db) << '\n';
        return false;
    }

    // Bind parameters in order of the "?"
    sqlite3_bind_text(stmt, 1, newName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, id);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

bool Database::UpdateGamePath(int id, std::string& newPath)
{
    std::string sql = "UPDATE GAMES SET PATH = ? WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Error preparing update: " << sqlite3_errmsg(db) << '\n';
        return false;
    }

    // Bind parameters in order of the "?"
    sqlite3_bind_text(stmt, 1, newPath.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, id);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

bool Database::UpdateGamePlaytime(int id, int newTotalSeconds) 
{
    std::string sql = "UPDATE GAMES SET PLAYTIME = ? WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) 
    {
        std::cerr << "Error preparing update: " << sqlite3_errmsg(db) << '\n';
        return false;
    }

    // Bind parameters in order of the "?"
    sqlite3_bind_int(stmt, 1, newTotalSeconds);
    sqlite3_bind_int(stmt, 2, id);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}