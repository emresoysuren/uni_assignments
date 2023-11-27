#pragma once

#include <ctime>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

/// @brief A class that provides some utility functions for the project
class Utils
{
private:
    template <typename T>
    static void swap(T *arr, int index1, int index2);

public:
    /// @brief Gets a date input from the user (clears the screen before getting input and validates the input).
    /// If the input is invalid, the user will be asked to enter a valid input.
    /// @param title The title of the input to be shown to the user to get input
    static std::tm getDateInput(std::string title);

    /// @brief Converts a string to a date from the format of dd-mm-yyyy
    static std::tm stringToDate(std::string str);

    /// @brief Converts a date to a string in the format of dd-mm-yyyy
    static std::string dateToString(std::tm date);

    /// @brief Splits a string into a vector of strings using the given delimiter
    static std::vector<std::string> spiltString(std::string str, char delimiter);

    /// @brief Clears the screen
    static void clearScreen();

    /// @brief Gets an input from the user (clears the screen before getting input)
    /// @param title The title of the input to be shown to the user to get input
    static std::string getInput(std::string title);

    /// @brief Gets multiple inputs from the user (clears the screen before getting input)
    /// @param titles The titles of the inputs to be shown to the user to get input
    /// @return Returns a vector of strings containing the inputs (same order and size as the titles vector)
    static std::vector<std::string> getMultipleInputs(std::vector<std::string> titles);

    /// @brief Gets multiple inputs from the user (clears the screen before getting input)
    /// @param mainTitle The title of the input to be shown to the user
    /// (This title will be shown before all the other titles and won't be used to get input)
    /// @param titles The titles of the inputs to be shown to the user to get input
    /// @return Returns a vector of strings containing the inputs (same order and size as the titles vector)
    static std::vector<std::string> getMultipleInputs(std::string mainTitle, std::vector<std::string> titles);

    /// @brief Generates a random key
    static std::string generateRandomKey();

    /// @brief Converts a time in seconds to a string in the format of mm:ss
    static std::string secondsToString(int seconds);

    static bool isDateBefore(std::tm date1, std::tm date2);

    template <typename T>
    static void quicksort(T *arr, std::function<bool(T, T)> isLess, int min, int max);

    template <typename T>
    static void quicksort(std::vector<T> *vec, std::function<bool(T, T)> isLess);
};

/// Template implementations

template <typename T>
void Utils::quicksort(std::vector<T> *vec, std::function<bool(T, T)> isLess)
{
    // Create an array with the same size as the vector
    T *arr = (T *)calloc(vec->size(), sizeof(T));

    // Copy the vector to an array
    for (int i = 0; i < vec->size(); i++)
    {
        arr[i] = (*vec)[i];
    }

    // Sort the array
    quicksort(arr, isLess, 0, vec->size());

    // Copy the sorted array to the vector
    for (int i = 0; i < vec->size(); i++)
    {
        (*vec)[i] = arr[i];
    }

    // Free the array
    delete arr;
}

template <typename T>
void Utils::quicksort(T *arr, std::function<bool(T, T)> isLess, int min, int max)
{
    if ((max - min) <= 1)
        return;

    int pivotIndex = min;
    swap(arr, max - 1, pivotIndex);
    pivotIndex = max - 1;

    int leftWall = min;

    for (int i = min; i < max - 1; i++)
    {
        if (!isLess(arr[pivotIndex], arr[i]))
        {
            swap(arr, i, leftWall);
            leftWall++;
        }
    }

    swap(arr, pivotIndex, leftWall);
    pivotIndex = leftWall;

    // Recursively sort the two partitions
    quicksort(arr, isLess, min, pivotIndex);
    quicksort(arr, isLess, pivotIndex + 1, max);
}

template <typename T>
void Utils::swap(T *arr, int index1, int index2)
{
    T temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}