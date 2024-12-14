/**
 * @file BaseFileManager.cpp
 * @brief Implementation of the BaseFileManager class for file and directory management.
 */

#include "BaseFileManager.h"
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;
namespace fs = filesystem;

/**
 * @brief Singleton pattern: Gets the single instance of BaseFileManager.
 * @return Reference to the BaseFileManager instance.
 */
BaseFileManager& BaseFileManager::getInstance() {
    static BaseFileManager instance;
    return instance;
}

/**
 * @brief Lists the contents of a directory.
 * @param path The path to the directory.
 * @param contents A vector to store the names of files and directories.
 * @return HTTP-like status code:
 * - 200: Success.
 * - 404: Directory does not exist.
 * - 400: Path is not a directory.
 * - 500: Other errors.
 */
int BaseFileManager::listDirectoryContents(const string& path, vector<string>& contents) {
    try {
        if (!fs::exists(path)) {
            cerr << "Error: Path does not exist." << endl;
            return 404;
        }
        if (!fs::is_directory(path)) {
            cerr << "Error: Path is not a directory." << endl;
            return 400;
        }
        for (const auto& entry : fs::directory_iterator(path)) {
            contents.push_back(entry.path().string());
        }
        return 200;
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Error accessing directory: " << e.what() << endl;
        return 500;
    }
}

/**
 * @brief Creates a file at the specified path.
 * @param path The path to the file to be created.
 * @return HTTP-like status code:
 * - 200: Success.
 * - 500: Error creating file.
 */
int BaseFileManager::createFile(const string& path) {
    try {
        ofstream file(path);
        if (!file) {
            cerr << "Error: Unable to create file." << endl;
            return 500;
        }
        return 200;
    }
    catch (const exception& e) {
        cerr << "Error creating file: " << e.what() << endl;
        return 500;
    }
}

/**
 * @brief Deletes a file at the specified path.
 * @param path The path to the file to be deleted.
 * @return HTTP-like status code:
 * - 200: Success.
 * - 404: File does not exist.
 * - 400: Path is not a regular file.
 * - 500: Other errors.
 */
int BaseFileManager::deleteFile(const string& path) {
    try {
        if (!fs::exists(path)) {
            cerr << "Error: File does not exist." << endl;
            return 404;
        }
        if (!fs::is_regular_file(path)) {
            cerr << "Error: Path is not a regular file." << endl;
            return 400;
        }
        fs::remove(path);
        return 200;
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Error deleting file: " << e.what() << endl;
        return 500;
    }
}

/**
 * @brief Creates a directory at the specified path.
 * @param path The path to the directory to be created.
 * @return HTTP-like status code:
 * - 200: Success.
 * - 400: Directory already exists.
 * - 500: Other errors.
 */
int BaseFileManager::createDirectory(const string& path) {
    try {
        if (fs::exists(path)) {
            cerr << "Error: Directory already exists." << endl;
            return 400;
        }
        fs::create_directory(path);
        return 200;
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Error creating directory: " << e.what() << endl;
        return 500;
    }
}

/**
 * @brief Deletes a directory at the specified path.
 * @param path The path to the directory to be deleted.
 * @return HTTP-like status code:
 * - 200: Success.
 * - 404: Directory does not exist.
 * - 400: Path is not a directory.
 * - 500: Other errors.
 */
int BaseFileManager::deleteDirectory(const string& path) {
    try {
        if (!fs::exists(path)) {
            cerr << "Error: Directory does not exist." << endl;
            return 404;
        }
        if (!fs::is_directory(path)) {
            cerr << "Error: Path is not a directory." << endl;
            return 400;
        }
        fs::remove_all(path);
        return 200;
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Error deleting directory: " << e.what() << endl;
        return 500;
    }
}

/**
 * @brief Renames or moves a file or directory.
 * @param oldPath The current path of the file or directory.
 * @param newPath The new path of the file or directory.
 * @return HTTP-like status code:
 * - 200: Success.
 * - 404: Source path does not exist.
 * - 500: Other errors.
 */
int BaseFileManager::rename(const string& oldPath, const string& newPath) {
    try {
        if (!fs::exists(oldPath)) {
            cerr << "Error: Source path does not exist." << endl;
            return 404;
        }
        fs::rename(oldPath, newPath);
        return 200;
    }
    catch (const fs::filesystem_error& e) {
        cerr << e.what() << endl;
        return 500;
    }
}

/**
 * @brief Searches for files matching a specific pattern within a directory and its subdirectories.
 * @param path The path to the directory to search in.
 * @param pattern The substring pattern to match filenames against.
 * @param results A vector to store the paths of the matching files.
 * @return HTTP-like status code:
 * - 200: Success, with results.
 * - 204: Success, but no matches found.
 * - 404: Directory does not exist.
 * - 400: Path is not a directory.
 * - 500: Other errors.
 */
int BaseFileManager::searchFiles(const string& path, const string& pattern, vector<string>& results) {
    try {
        if (!fs::exists(path)) {
            cerr << "Error: Directory does not exist." << endl;
            return 404;
        }

        if (!fs::is_directory(path)) {
            cerr << "Error: Path is not a directory." << endl;
            return 400;
        }

        for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
            if (entry.path().filename().string().find(pattern) != string::npos) {
                results.push_back(entry.path().string());
            }
        }

        return results.empty() ? 204 : 200;
    }
    catch (const fs::filesystem_error& e) {
        cerr << e.what() << endl;
        return 500;
    }
}
