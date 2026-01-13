#include "Application.h"

Application::Application()
	: m_db(m_dbPath), 
	m_window("Pulse Launcher", 1280, 720),
	m_ui(m_window.GetNativeWindow(), &m_db, &m_launcher)
{

}

Application::~Application()
{

}

void Application::Initialize()
{

}

void Application::Cleanup()
{

}

// Runs every frame
void Application::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	m_ui.Render();

	ImGui::Render();

	int display_w, display_h;
	glfwGetFramebufferSize(m_window.GetNativeWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	m_window.OnUpdate();
}

void Application::Run()
{
	auto games = m_db.GetAllGames();

	for (const auto& game : games) 
	{
		std::cout << "Found: " << game.name << " | ID: " << game.id << std::endl;
	}

	// Render loop
	while (m_window.IsOpen())
	{
		Update();
	}
}