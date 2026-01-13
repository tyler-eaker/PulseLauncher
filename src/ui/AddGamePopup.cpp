#include "AddGamePopup.h"

AddGamePopup::AddGamePopup(DatabaseService* db, GameListView* gameListView)
    : m_db(db), m_gameListView(gameListView)
{

}

void AddGamePopup::Render()
{
    ImGui::Begin("Add Game", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

    static char pathBuffer[1024] = "";
    static char nameBuffer[64] = "";

    ImGui::InputText("Path", pathBuffer, sizeof(pathBuffer));
    ImGui::SameLine();

    if (ImGui::Button("Browse..."))
    {
        const char* filters[1] = { "*.exe" };
        char* selectedFile = tinyfd_openFileDialog("Select Game Executable", NULL, 1, filters, "Executables", 0);

        if (selectedFile)
        {
            strncpy_s(pathBuffer, selectedFile, sizeof(pathBuffer) - 1);
        }
    }

    ImGui::InputText("Game Name", nameBuffer, sizeof(nameBuffer));

    if (ImGui::Button("Save to Library"))
    {
        if (pathBuffer[0] != '\0')
        {
            if (nameBuffer[0] == '\0')
            {
                auto gameNum = m_db->GetAllGames().size() + 1;
                std::string name = "Game " + std::to_string(gameNum);

                m_db->AddGame(name, pathBuffer);
            }
            else
            {
                m_db->AddGame(nameBuffer, pathBuffer);
            }

            memset(nameBuffer, 0, sizeof(nameBuffer));
            memset(pathBuffer, 0, sizeof(pathBuffer));
        }

        m_gameListView->RefreshList();
    }

    ImGui::End();
}
