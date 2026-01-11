#include "Window.h"

Window::Window(std::string& title, int sizeX, int sizeY) 
    : windowTitle(title), windowSizeX(sizeX), windowSizeY(sizeY)
{
    Initialize();
}

Window::~Window()
{
    Cleanup();
}

GLFWwindow* Window::GetWindow()
{
    return window;
}

// Standard GLFW error callback
static void glfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void Window::Initialize()
{
    glfwSetErrorCallback(glfwErrorCallback);

    // 1. Init GLFW
    if (!glfwInit())
    {
        std::cerr << "CRITICAL ERROR: Failed to initialize GLFW.\n";
        std::cin.get(); // Pause to read error
        exit(-1);
    }

    // --- NEW: Add these hints BEFORE creating the window ---
    // This requests OpenGL 3.3 Core Profile, which is standard for modern ImGui
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Good for Mac/Forward compat
    // -------------------------------------------------------

    // 2. Create window
    this->window = glfwCreateWindow(windowSizeX, windowSizeY, windowTitle.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
        // Print the specific error from GLFW logic
        const char* description;
        int code = glfwGetError(&description);

        std::cerr << "CRITICAL ERROR: Failed to create GLFW Window.\n";
        if (description)
            std::cerr << "GLFW Details: " << description << "\n";

        std::cerr << "Press Enter to exit...";
        std::cin.get();
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
}

void Window::Cleanup()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}