#include "Application.h"

Application::Application()
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
	while (running)
	{
		Update();
	}
}

// Gets called each frame
void Application::Update()
{

}

void Application::Cleanup()
{

}
