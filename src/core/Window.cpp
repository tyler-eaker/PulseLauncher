#include "Window.h"

// Static error callback for GLFW
static void GLFWErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

Window::Window(std::string title, int width, int height)
{
	m_data.title = title;
	m_data.width = width;
	m_data.height = height;

	Initialize();
}

Window::~Window()
{
	Cleanup();
}

void Window::Initialize()
{
	glfwSetErrorCallback(GLFWErrorCallback);

	if (!glfwInit())
	{
		std::cerr << "ERROR: Failed to initialize GLFW.\n";
		std::cin.get();
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);

	if (!m_window)
	{
		std::cerr << "ERROR: Failed to create GLFW window.\n";
		std::cin.get();
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(m_data.vsync);

	glfwSetWindowUserPointer(m_window, &m_data);
}

void Window::Cleanup()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
}

void Window::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

bool Window::IsOpen() const
{
	return !glfwWindowShouldClose(m_window);
}

int Window::GetWidth() const
{
	return m_data.width;
}

int Window::GetHeight() const
{
	return m_data.height;
}

GLFWwindow* Window::GetNativeWindow() const
{
	return m_window;
}