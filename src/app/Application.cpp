#include "Application.h"

Application::Application()
	: window(windowTitle, 1280, 720)
{
	Initialize();
}

Application::~Application()
{
	Cleanup();
}

void Application::Initialize()
{
	this->db = new Database(dbPath);
}

void Application::Run()
{
	bool running = true;

	// Basic application loop
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glfwPollEvents();

		glfwGetFramebufferSize(window.GetWindow(), &windowSizeX, &windowSizeY);
		glViewport(0, 0, windowSizeX, windowSizeY);

		// Clear background color (Dark Grey)
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window.GetWindow());
	}
}

// Gets called each frame
void Application::Update()
{

}

void Application::Cleanup()
{
	delete this->db;
}
