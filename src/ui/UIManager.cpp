#include "UIManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

UIManager::UIManager(GLFWwindow* window, DatabaseService* db, LauncherService* launcher)
    : m_gameListView(db, launcher), m_addGamePopup(db, &m_gameListView)
{
    Initialize(window);
}

UIManager::~UIManager()
{
    Cleanup();
}

void UIManager::Render()
{
    // m_mainLayout.Render();
    m_gameListView.Render();
    m_addGamePopup.Render();
}

void UIManager::Initialize(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    if (fs::exists(m_fontPath))
    {
        // Set global UI font
        io.Fonts->Clear();
        ImFont* font = io.Fonts->AddFontFromFileTTF(m_fontPath.c_str(), 22.0f);
    }

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void UIManager::Cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
