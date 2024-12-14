/**
 * @file BaseFileManager.h
 * @brief Declares the BaseFileManager class, which provides file management operations.
 */

#ifndef BASE_FILE_MANAGER_H
#define BASE_FILE_MANAGER_H

#include <string>
#include <vector>

 /**
  * @class BaseFileManager
  * @brief Singleton class for managing file and directory operations.
  */
class BaseFileManager {
public:
    /**
     * @brief Retrieves the singleton instance of the BaseFileManager.
     * @return Reference to the BaseFileManager instance.
     */
    static BaseFileManager& getInstance();

    /**
     * @brief Lists the contents of a directory.
     * @param path Path to the directory.
     * @param contents Vector to store directory contents.
     * @return Status code (200 - success, 404 - not found, etc.).
     */
    int listDirectoryContents(const std::string& path, std::vector<std::string>& contents);

    /**
     * @brief Creates a new file at the specified path.
     * @param path Path to the file.
     * @return Status code.
     */
    int createFile(const std::string& path);

    /**
     * @brief Deletes a file at the specified path.
     * @param path Path to the file.
     * @return Status code.
     */
    int deleteFile(const std::string& path);

    /**
     * @brief Creates a directory at the specified path.
     * @param path Path to the directory.
     * @return Status code.
     */
    int createDirectory(const std::string& path);

    /**
     * @brief Deletes a directory at the specified path.
     * @param path Path to the directory.
     * @return Status code.
     */
    int deleteDirectory(const std::string& path);

    /**
     * @brief Renames a file or directory.
     * @param oldPath Current path of the file/directory.
     * @param newPath New path for the file/directory.
     * @return Status code.
     */
    int rename(const std::string& oldPath, const std::string& newPath);

    /**
     * @brief Searches for files matching a pattern in a directory.
     * @param path Directory path to search in.
     * @param pattern Filename pattern to search for.
     * @param results Vector to store matching files.
     * @return Status code.
     */
    int searchFiles(const std::string& path, const std::string& pattern, std::vector<std::string>& results);

private:
    /**
     * @brief Private constructor for the singleton pattern.
     */
    BaseFileManager() = default;

    /**
     * @brief Private destructor for the singleton pattern.
     */
    ~BaseFileManager() = default;
};

#endif // BASE_FILE_MANAGER_H