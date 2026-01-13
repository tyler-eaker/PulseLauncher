#include "AddGamePopup.h"

AddGamePopup::AddGamePopup(DatabaseService* db)
    : m_db(db)
{

}

void AddGamePopup::Render()
{
    static char pathBuffer[1024] = "";

    ImGui::InputText("Path", pathBuffer, sizeof(pathBuffer));
    ImGui::SameLine();

    if (ImGui::Button("Add Game..."))
    {
        const char* filters[1] = { "*.exe" };

        // Arguments: Title, Default Path, Num Filters, Filter Patterns, Description, Allow Multiple Selects
        char* selectedFile = tinyfd_openFileDialog(
            "Select Game Executable",
            NULL,
            1,
            filters,
            "Executables",
            0
        );

        if (selectedFile)
        {
            // Copy the result into text buffer
            strncpy_s(pathBuffer, selectedFile, sizeof(pathBuffer) - 1);

            m_db->AddGame("test game", pathBuffer);
        }
    }
}
