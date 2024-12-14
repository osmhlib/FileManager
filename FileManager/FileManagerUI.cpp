/**
 * @file FileManagerUI.cpp
 * @brief Implementation of the user interface for the File Manager.
 */

#include "FileManagerUI.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Constructor for initializing the FileManagerUI with a BaseFileManager instance.
 * @param manager Reference to the BaseFileManager instance to interact with file system operations.
 */
FileManagerUI::FileManagerUI(BaseFileManager& manager) : manager(manager) {}

/**
 * @brief Main loop to run the File Manager user interface.
 * Displays menu options and processes user commands until the exit command is issued.
 */
void FileManagerUI::start() {
    string command;

    while (true) {
        cout << "\n=== File Manager ===\n";
        cout << "1. Create File\n";
        cout << "2. Delete File\n";
        cout << "3. Create Directory\n";
        cout << "4. Delete Directory\n";
        cout << "5. List Directory Contents\n";
        cout << "6. Rename File/Directory\n";
        cout << "7. Search Files\n";
        cout << "8. Clear Console\n";
        cout << "9. Exit\n";

        cout << "\nEnter command: ";
        getline(cin, command);

        if (command == "9") {
            char confirm;
            cout << "\nAre you sure you want to exit? (y/n): ";
            cin >> confirm;
            cin.ignore();

            if (confirm == 'y' || confirm == 'Y') {
                cout << "\nGoodbye!\n";
                break;
            }
            else {
                continue;
            }
        }

        processCommand(command);
    }
}

/**
 * @brief Processes user commands and invokes appropriate file operations.
 * @param command User input corresponding to a menu option.
 */
void FileManagerUI::processCommand(const string& command) {
    switch (stoi(command)) {
    case 1:
        createFile();
        break;
    case 2:
        deleteFile();
        break;
    case 3:
        createDirectory();
        break;
    case 4:
        deleteDirectory();
        break;
    case 5:
        listDirectoryContents();
        break;
    case 6:
        renameItem();
        break;
    case 7:
        searchFiles();
        break;
    case 8:
        clearConsoleWithConfirmation();
        break;
    case 9:
        break; // Exit is handled in `start()`
    default:
        cout << "\nUnknown command. Please try again.\n";
    }
}

/**
 * @brief Prompts user for a file path and creates a new file.
 */
void FileManagerUI::createFile() {
    string path;
    cout << "\nEnter file path: ";
    getline(cin, path);
    int statusCode = manager.createFile(path);
    handleStatus(statusCode);
}

/**
 * @brief Prompts user for a file path and deletes the specified file with confirmation.
 */
void FileManagerUI::deleteFile() {
    string path;
    cout << "\nEnter file path: ";
    getline(cin, path);
    cout << "\nAre you sure you want to delete this file? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
        int statusCode = manager.deleteFile(path);
        handleStatus(statusCode);
    }
    else {
        cout << "\nOperation canceled.\n";
    }
}

/**
 * @brief Prompts user for a directory path and creates a new directory.
 */
void FileManagerUI::createDirectory() {
    string path;
    cout << "\nEnter directory path: ";
    getline(cin, path);
    int statusCode = manager.createDirectory(path);
    handleStatus(statusCode);
}

/**
 * @brief Prompts user for a directory path and deletes the specified directory with confirmation.
 */
void FileManagerUI::deleteDirectory() {
    string path;
    cout << "\nEnter directory path: ";
    getline(cin, path);
    cout << "\nAre you sure you want to delete this directory? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
        int statusCode = manager.deleteDirectory(path);
        handleStatus(statusCode);
    }
    else {
        cout << "\nOperation canceled.\n";
    }
}

/**
 * @brief Lists the contents of a specified directory.
 */
void FileManagerUI::listDirectoryContents() {
    string path;
    vector<string> contents;

    cout << "\nEnter directory path: ";
    getline(cin, path);
    int statusCode = manager.listDirectoryContents(path, contents);
    handleStatus(statusCode);

    if (statusCode == 200) {
        cout << "\nDirectory Contents:\n";

        for (const auto& item : contents) {
            cout << "- " + item + "\n";
        }
    }
}

/**
 * @brief Renames a file or directory from a specified old name to a new name.
 */
void FileManagerUI::renameItem() {
    string oldPath, newPath;

    cout << "\nEnter current file/directory path: ";
    getline(cin, oldPath);

    cout << "Enter new name for the file/directory: ";
    getline(cin, newPath);

    int statusCode = manager.rename(oldPath, newPath);
    handleStatus(statusCode);
}

/**
 * @brief Searches for files matching a pattern in a specified directory and its subdirectories.
 */
void FileManagerUI::searchFiles() {
    string path, pattern;
    vector<string> results;

    cout << "\nEnter directory path to search: ";
    getline(cin, path);
    cout << "Enter filename pattern to search for: ";
    getline(cin, pattern);

    int statusCode = manager.searchFiles(path, pattern, results);
    handleStatus(statusCode);

    if (statusCode == 200) {
        cout << "\nSearch Results:\n";
        for (const auto& item : results) {
            cout << "- " + item + "\n";
        }
    }
}

/**
 * @brief Clears the console screen after a confirmation prompt.
 */
void FileManagerUI::clearConsoleWithConfirmation() {
    char confirm;
    cout << "\nAre you sure you want to clear the console? (y/n): ";
    cin >> confirm;
    cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        cout << "\nConsole cleared.\n";
    }
    else {
        cout << "\nOperation canceled.\n";
    }
}

/**
 * @brief Handles and outputs a message corresponding to a file system operation status code.
 * @param statusCode Status code returned by a file system operation.
 */
void FileManagerUI::handleStatus(int statusCode) {
    switch (statusCode) {
    case 200:
        cout << "\nOperation successful.\n";
        break;
    case 204:
        cout << "\nNo files found matching the criteria.\n";
        break;
    case 400:
        cout << "\nError: Invalid path or resource already exists.\n";
        break;
    case 404:
        cout << "\nError: File or directory not found.\n";
        break;
    case 500:
        cout << "\nError: System error occurred. Please check your input or permissions.\n";
        break;
    default:
        cout << "\nUnknown status code: " << statusCode << "\n";
        break;
    }
}
