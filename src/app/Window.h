#pragma once

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <string>

class Window
{
public:
	Window() = default;

	Window(std::string& title, int sizeX, int sizeY);
	~Window();

	std::string windowTitle;
	int windowSizeX;
	int windowSizeY;

	GLFWwindow* GetWindow();

private:
	GLFWwindow* window = nullptr;

	void Initialize();
	void Cleanup();
};