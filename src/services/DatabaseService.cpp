#include "DatabaseService.h"

DatabaseService::DatabaseService()
{
    Initialize();
}

DatabaseService::~DatabaseService()
{
    Cleanup();
}

void DatabaseService::Initialize()
{
    CreateDirectory();
    OpenDatabase();
}

void DatabaseService::Cleanup()
{
    if (m_db)
    {
        sqlite3_close(m_db);
    };
}

void DatabaseService::CreateDirectory()
{
    char* appDataPath = nullptr;
    size_t len = 0;

    if (_dupenv_s(&appDataPath, &len, "APPDATA") == 0 && appDataPath != nullptr)
    {
        // Path: C:\Users\User\AppData\Roaming\PulseLauncher
        fs::path configDir = fs::path(appDataPath) / "PulseLauncher";

        if (!fs::exists(configDir)) {

            std::cout << "Database path not found.\n";
            std::cout << "Creating database directory...\n";

            if (fs::create_directories(configDir))
            {
                std::cout << "Database directory created.\n";
            }

        }

        m_path = (configDir / "launcher.db").string();
        free(appDataPath);
    }
    else
    {
        m_path = "launcher.db"; // Fallback, creates in the PulseLauncher.exe path
    }

    std::cout << "Database Path: " << m_path << "\n\n";
}

void DatabaseService::OpenDatabase()
{
    std::cout << "Opening database...\n";

    // Open the database connection
    int exit = sqlite3_open(m_path.c_str(), &m_db);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error opening DB: " << sqlite3_errmsg(m_db) << '\n';
    }
    else
    {
        std::cout << "Database opened successfully!\n\n";

        std::cout << "Creating table...\n";

        // Create the table if it doesn't exist
        std::string sql =
            "CREATE TABLE IF NOT EXISTS GAMES("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "NAME           TEXT    NOT NULL, "
            "PATH           TEXT    NOT NULL, "
            "PLAYTIME       INT     DEFAULT 0);";

        char* messageError;
        int exit = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK)
        {
            std::cerr << "Error Creating Table: " << messageError << '\n';
            sqlite3_free(messageError);
        }
        else
        {
            std::cout << "Table initialized.\n\n";
        }

        this->m_games = GetAllGames();
    }
}

bool DatabaseService::GameExists(const std::string& path)
{
    std::string sql = "SELECT 1 FROM GAMES WHERE PATH = ? LIMIT 1;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Error checking existence: " << sqlite3_errmsg(m_db) << '\n';
        return false;
    }

    sqlite3_bind_text(stmt, 1, path.c_str(), -1, SQLITE_TRANSIENT);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return (result == SQLITE_ROW);
}

Game DatabaseService::GetGame(int id)
{
    Game game = {}; // Empty game object
    game.id = -1;   // Flag to indicate "not found"

    std::string sql = "SELECT * FROM GAMES WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) 
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(m_db) << '\n';
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

std::vector<Game> DatabaseService::GetAllGames()
{
    std::vector<Game> games;
    const char* sql = "SELECT * FROM GAMES;";

    // We pass &games as the "data" argument so the callback can fill it
    sqlite3_exec(m_db, sql, callback, &games, NULL);

    return games;
}

std::string DatabaseService::GetDBPath()
{
    return m_path;
}

bool DatabaseService::AddGame(const std::string& name, const std::string& path)
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

    if (sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
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

bool DatabaseService::UpdateGameName(int id, std::string& newName)
{
    std::string sql = "UPDATE GAMES SET NAME = ? WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Error preparing update: " << sqlite3_errmsg(m_db) << '\n';
        return false;
    }

    // Bind parameters in order of the "?"
    sqlite3_bind_text(stmt, 1, newName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, id);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

bool DatabaseService::UpdateGamePath(int id, std::string& newPath)
{
    std::string sql = "UPDATE GAMES SET PATH = ? WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Error preparing update: " << sqlite3_errmsg(m_db) << '\n';
        return false;
    }

    // Bind parameters in order of the "?"
    sqlite3_bind_text(stmt, 1, newPath.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, id);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

bool DatabaseService::UpdateGamePlaytime(int id, int newTotalSeconds)
{
    std::string sql = "UPDATE GAMES SET PLAYTIME = ? WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Error preparing update: " << sqlite3_errmsg(m_db) << '\n';
        return false;
    }

    // Bind parameters in order of the "?"
    sqlite3_bind_int(stmt, 1, newTotalSeconds);
    sqlite3_bind_int(stmt, 2, id);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}