#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;

/**
 * @class BaseFileManager
 * @brief Provides basic file management operations like listing, creating, deleting, renaming files and directories.
 *
 * This class uses the <filesystem> library to perform basic file and directory operations.
 * It serves as a base for interacting with the file system through encapsulated methods.
 */
class BaseFileManager {
public:
    /**
     * @brief Lists the contents of a specified directory.
     *
     * @param path The directory path to list contents of.
     *
     * Prints each item (file or directory) in the specified directory.
     */
    void listDirectoryContents(const string& path) {
        if (!filesystem::exists(path) || !filesystem::is_directory(path)) {
            cerr << "Invalid directory path!" << endl;
            return;
        }
        for (const auto& entry : filesystem::directory_iterator(path)) {
            cout << entry.path().filename() << endl;
        }
    }

    /**
     * @brief Creates a new file at the specified path.
     *
     * @param filePath The path where the file should be created.
     *
     * Prints a message indicating success or failure of file creation.
     */
    void createFile(const string& filePath) {
        ofstream file(filePath);
        if (file) {
            cout << "File created: " << filePath << endl;
        }
        else {
            cerr << "Error creating file: " << filePath << endl;
        }
    }

    /**
     * @brief Deletes a file at the specified path.
     *
     * @param filePath The path of the file to delete.
     *
     * Prints a message indicating success or failure of file deletion.
     */
    void deleteFile(const string& filePath) {
        if (filesystem::remove(filePath)) {
            cout << "File deleted: " << filePath << endl;
        }
        else {
            cerr << "Error deleting file: " << filePath << endl;
        }
    }

    /**
     * @brief Creates a new directory at the specified path.
     *
     * @param dirPath The path where the directory should be created.
     *
     * Prints a message indicating success or failure of directory creation.
     */
    void createDirectory(const string& dirPath) {
        if (filesystem::create_directory(dirPath)) {
            cout << "Directory created: " << dirPath << endl;
        }
        else {
            cerr << "Error creating directory: " << dirPath << endl;
        }
    }

    /**
     * @brief Deletes a directory and all its contents at the specified path.
     *
     * @param dirPath The path of the directory to delete.
     *
     * Prints a message indicating success or failure of directory deletion.
     */
    void deleteDirectory(const string& dirPath) {
        if (filesystem::remove_all(dirPath)) {
            cout << "Directory deleted: " << dirPath << endl;
        }
        else {
            cerr << "Error deleting directory: " << dirPath << endl;
        }
    }

    /**
     * @brief Renames a file or directory from oldPath to newPath.
     *
     * @param oldPath The current path of the file or directory.
     * @param newPath The new path for the file or directory.
     *
     * Prints a message indicating success or failure of the renaming operation.
     */
    void rename(const string& oldPath, const string& newPath) {
        try {
            filesystem::rename(oldPath, newPath);
            cout << "Renamed from " << oldPath << " to " << newPath << endl;
        }
        catch (const filesystem::filesystem_error& e) {
            cerr << "Error renaming: " << e.what() << endl;
        }
    }

    /**
     * @brief Searches for files containing the specified query in their name within a directory.
     *
     * @param directory The directory path to search within.
     * @param query The name or extension to search for.
     *
     * Prints paths of all files that match the query. If no matches are found, informs the user.
     */
    void searchFiles(const string& directory, const string& query) {
        if (!filesystem::exists(directory) || !filesystem::is_directory(directory)) {
            cerr << "Invalid directory path!" << endl;
            return;
        }
        bool found = false;
        for (const auto& entry : filesystem::recursive_directory_iterator(directory)) {
            if (entry.path().filename().string().find(query) != string::npos) {
                cout << entry.path() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No files found matching: " << query << endl;
        }
    }
};

/**
 * @class FileManagerUI
 * @brief Provides a user interface to interact with the BaseFileManager functionalities.
 *
 * This class is responsible for displaying a menu, receiving user inputs, and calling appropriate
 * methods in BaseFileManager based on the user's selection.
 */
class FileManagerUI {
private:
    BaseFileManager manager; ///< An instance of BaseFileManager to perform file operations.

public:
    /**
     * @brief Displays the main menu with options for file management.
     *
     * Prints a list of actions that the user can perform in the file manager.
     */
    void showMenu() {
        cout << "\nFile Manager Menu:\n";
        cout << "1. List directory contents\n";
        cout << "2. Create a file\n";
        cout << "3. Delete a file\n";
        cout << "4. Create a directory\n";
        cout << "5. Delete a directory\n";
        cout << "6. Rename a file or directory\n";
        cout << "7. Search files by name or extension\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";
    }

    /**
     * @brief Starts the file manager UI and waits for user input to perform actions.
     *
     * Repeatedly displays the menu, receives user choices, and executes the corresponding
     * file management operations until the user chooses to exit.
     */
    void start() {
        int choice;
        string path, newPath, query;

        do {
            showMenu();
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter directory path: ";
                cin >> path;
                manager.listDirectoryContents(path);
                break;
            case 2:
                cout << "Enter file path to create: ";
                cin >> path;
                manager.createFile(path);
                break;
            case 3:
                cout << "Enter file path to delete: ";
                cin >> path;
                manager.deleteFile(path);
                break;
            case 4:
                cout << "Enter directory path to create: ";
                cin >> path;
                manager.createDirectory(path);
                break;
            case 5:
                cout << "Enter directory path to delete: ";
                cin >> path;
                manager.deleteDirectory(path);
                break;
            case 6:
                cout << "Enter current file/directory path: ";
                cin >> path;
                cout << "Enter new file/directory path: ";
                cin >> newPath;
                manager.rename(path, newPath);
                break;
            case 7:
                cout << "Enter directory path to search in: ";
                cin >> path;
                cout << "Enter file name or extension to search: ";
                cin >> query;
                manager.searchFiles(path, query);
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    FileManagerUI ui;
    ui.start();
    return 0;
}