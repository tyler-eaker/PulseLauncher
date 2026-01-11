#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Window.h"

class GUI
{
public:
	GUI() = default;

	GUI(GLFWwindow* window);
	~GUI();

private:
	GLFWwindow* window;

	void Initialize();
	void Cleanup();
};