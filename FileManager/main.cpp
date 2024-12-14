/**
 * @file main.cpp
 * @brief Entry point for the File Manager application.
 */

#include "FileManagerUI.h"
#include "BaseFileManager.h"
#include <Windows.h>

 /**
  * @brief Main function to start the File Manager application.
  * Sets up the console encoding to support specific character sets
  * and initializes the file manager and user interface.
  * @return int Exit status of the program.
  */
int main() {
    // Set console input and output encoding to Windows-1251 for proper character display.
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Obtain the singleton instance of the file manager.
    BaseFileManager& manager = BaseFileManager::getInstance();

    // Initialize the user interface with the file manager instance.
    FileManagerUI ui(manager);

    // Start the user interface.
    ui.start();

    return 0; // Indicate successful program termination.
}