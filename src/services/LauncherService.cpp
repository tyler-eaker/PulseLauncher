#include "LauncherService.h"

LauncherService::LauncherService()
{

}

LauncherService::~LauncherService()
{

}

void LauncherService::LaunchGame(const std::string& path)
{
    std::cout << "Attempting to launch:\n" << path << '\n';

    HINSTANCE result = ShellExecuteA(
        NULL,           // Parent window handle
        "open",         // Operation to perform
        path.c_str(),   // File or object to operate on
        NULL,           // Parameters
        NULL,           // Default directory
        SW_SHOWNORMAL   // How the window is shown
    );

    if ((int)result <= 32) {
        std::cerr << "Launch failed.\n";
    }

    std::cout << "Application launched successfully!\n";
}
