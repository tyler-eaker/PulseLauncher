#include "Application.h"

Application::Application()
    : db(dbPath),
    window(windowTitle, 1280, 720),
    gui(window.GetWindow())
{
    Initialize();
}

Application::~Application()
{
	Cleanup();
}

void Application::Initialize()
{
	
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		Update();
	}
}

// Gets called each frame
void Application::Update()
{
    // Poll events (keyboard, mouse, window resize)
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // -------------------------------------------------------
    // UI CODE GOES HERE
    // -------------------------------------------------------

    // Create a window called "My Games"
    ImGui::Begin("My Games Library");

    if (ImGui::Button("Add New Game")) {
        ImGui::OpenPopup("AddGamePopup");
    }

    // Display List of Games
    // (In a real app, don't fetch from DB every frame! Cache this in a vector)
    auto games = db.GetAllGames();

    ImGui::Separator();

    for (const auto& game : games) {
        ImGui::Text("%s", game.name.c_str());
        ImGui::SameLine();
        if (ImGui::Button(("Launch##" + std::to_string(game.id)).c_str())) {
            // Phase 2/3 code will go here!
            printf("Launching %s...\n", game.name.c_str());
        }
    }

    ImGui::End();
    // -------------------------------------------------------

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window.GetWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    // Clear background color (Dark Grey)
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw ImGui
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window.GetWindow());
}

void Application::Cleanup()
{
	
}
