#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Utils.h"

/// @brief The base class for all the classes that need to be stored in files
/// (provides an easy interface for storing and retrieving data)
class StorableUnit
{
private:
    /// @brief Joins the given vector of arg strings into a single string
    /// using the ';' character as a delimiter to be stored in the file as a single line
    /// @return Returns the joined string of args
    std::string getFormatedArgs() const;

protected:
    /// @brief The path to the file where the data is stored
    std::string virtual getPath() const = 0;

    /// @brief The args of the object to be stored in the file as a single line
    /// and its first arg is the primary key
    /// @return Returns a vector of strings where each string is an arg of the object
    std::vector<std::string> virtual getArgs() const = 0;

    /// @brief Finds the corresponding line in the file that contains the object's primary key
    /// and returns it as a vector of strings where each string is an arg of the object
    /// @return Returns a vector of strings where each string is an arg of the object
    std::vector<std::string> getStored() const;

    /// @brief Finds the corresponding line in the file that contains the given key
    /// and returns it as a vector of strings where each string is an arg of the object
    /// @param path The path to the file to search in
    /// @param key The key is the primary key of the object
    /// @return Returns a vector of strings where each string is an arg of the object
    static std::vector<std::string> getStored(std::string path, std::string key);

    /// @brief Deletes the line that contains the object's primary key from the file in the path
    void deleteStored() const;

    /// @brief Saves the object using its args to the file in the path
    /// @param uniquePrimary If true, the primary key will be checked to be unique before saving the object
    void save(bool uniquePrimary = true) const;

    /// @brief Resaves the object using its args to the file in the path
    /// (deletes the old line with the same primary key and saves the new one).
    /// Do not use if the primary key is not unique.
    void resave() const;

    /// @brief Generates a unique primary key for the object in the given file
    /// @param path The path to the file to search in
    /// @return Returns the generated unique primary key
    static std::string generateUniquePrimaryKey(std::string path);

    /// @brief Gets all the lines that consist of the args of objects in the given file using its path
    /// @param path The path to the file to search in
    /// @return Returns a vector of vectors of strings
    /// where each vector of strings is a vector of args in a single line
    static std::vector<std::vector<std::string>> getAllStored(std::string path);

    /// @brief Checks if the given key is unique in the given file
    /// @param path The path to the file to search in
    /// @param key The key to check if it is unique
    /// @param onlyPrimary If true, only the primary key will be checked to be unique
    /// @return Returns true if the key is unique and false otherwise
    static bool isKeyUnique(std::string path, std::string key, bool onlyPrimary);

    /// @brief Checks if the given key is unique in the given file (Checks all the args)
    /// @param path The path to the file to search in
    /// @param key The key to check if it is unique
    /// @return Returns true if the key is unique and false otherwise
    static bool isKeyUnique(std::string path, std::string key);

    /// @brief Checks if the given key is unique in the file of the object
    /// @param key The key to check if it is unique
    /// @return Returns true if the key is unique and false otherwise
    bool isKeyUnique(std::string key) const;

    /// @brief Deletes the line that contains the given key from the file (Checks all the args)
    static void deleteOnAnyMatch(std::string path, std::string key);

    /// @brief Finds all the keys that contain the given key
    /// @param path The path to the file to search in
    /// @param key The key to search for
    /// @param findFirst If true, only the first line that contains the given key will be returned
    /// @return Returns a vector of vectors of strings
    /// where each vector of strings is a vector of args in a single line
    /// that contains the given key from the file
    static std::vector<std::vector<std::string>> findKeysContains(std::string path, std::string key, bool findFirst = false);
};
