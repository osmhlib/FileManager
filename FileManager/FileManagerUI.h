/**
 * @file FileManagerUI.h
 * @brief Declares the FileManagerUI class, which provides a console-based user interface for file management.
 */

#ifndef FILE_MANAGER_UI_H
#define FILE_MANAGER_UI_H

#include "BaseFileManager.h"
#include <string>

 /**
  * @class FileManagerUI
  * @brief User interface for interacting with the BaseFileManager.
  */
class FileManagerUI {
private:
    /**
     * @brief Reference to the BaseFileManager instance.
     */
    BaseFileManager& manager;

    /**
     * @brief Handles status codes and provides user feedback.
     * @param statusCode Status code from file operations.
     */
    void handleStatus(int statusCode);

    /**
     * @brief Processes a user command.
     * @param command User command as a string.
     */
    void processCommand(const std::string& command);

    // Specific command handlers
    void createFile();
    void deleteFile();
    void createDirectory();
    void deleteDirectory();
    void listDirectoryContents();
    void renameItem();
    void clearConsoleWithConfirmation();
    void searchFiles();

public:
    /**
     * @brief Constructs the FileManagerUI.
     * @param manager Reference to the BaseFileManager instance.
     */
    explicit FileManagerUI(BaseFileManager& manager);

    /**
     * @brief Starts the interactive console UI.
     */
    void start();
};

#endif // FILE_MANAGER_UI_H