#include "GameListView.h"

GameListView::GameListView(DatabaseService* db, LauncherService* launcher)
    : m_db(db), m_launcher(launcher)
{

}

void GameListView::Render()
{
    if (m_needsRefresh)
    {
        m_gamesCache = m_db->GetAllGames();
        m_needsRefresh = false;
    }

    bool open = NULL;

    ImGui::Begin("My Library", &open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

    ImGui::Separator();

    if (ImGui::BeginTable("GamesTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 30.0f);
        ImGui::TableSetupColumn("Game Name", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, 80.0f);
        ImGui::TableHeadersRow();

        for (const auto& game : m_gamesCache)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", game.id);

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", game.name.c_str());

            ImGui::TableSetColumnIndex(2);
            std::string btnLabel = "Play##" + std::to_string(game.id);

            if (ImGui::Button(btnLabel.c_str()))
            {
                m_launcher->LaunchGame(game.path);
            }
        }
        ImGui::EndTable();
    }

    ImGui::End();
}

void GameListView::RefreshList()
{
    m_needsRefresh = true;
}