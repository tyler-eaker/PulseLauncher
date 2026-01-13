#pragma once

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <string>

class Window
{
public:
	Window(std::string title, int width, int height);
	~Window();

	// Disallow copying of window
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	// Helpers
	void OnUpdate();
	bool IsOpen() const;

	// Getters
	int GetWidth() const;
	int GetHeight() const;

	GLFWwindow* GetNativeWindow() const;

private:
	GLFWwindow* m_window = nullptr;

	struct WindowData
	{
		std::string title;
		int width;
		int height;
		bool vsync = true;
	};
	WindowData m_data;

	// Internal Helpers
	void Initialize();
	void Cleanup();
};