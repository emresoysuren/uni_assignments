#pragma once

#include <ctime>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <functional>

/// @brief A class that provides some utility functions for the project
class Utils
{
private:
    /// @brief Swaps two elements in an array
    /// @tparam T The type of the elements in the array
    /// @param arr The array to swap the elements in
    /// @param index1 The index of the first element to swap
    /// @param index2 The index of the second element to swap
    template <typename T>
    static void swap(T *arr, int index1, int index2);

    /// @brief Clears and ingores the cin buffer
    static void cinIgnore();

public:
    /// @brief Gets a date input from the user (clears the screen before getting input and validates the input).
    /// If the input is invalid, the user will be asked to enter a valid input.
    /// @param title The title of the input to be shown to the user to get input
    static std::tm getDateInput(std::string title);

    /// @brief Converts a string to a date from the format of dd-mm-yyyy
    static std::tm stringToDate(std::string str);

    /// @brief Converts a date to a string in the format of dd-mm-yyyy
    static std::string dateToString(std::tm date);

    /// @brief Gets a int input from the user (clears the screen before getting input and validates the input).
    /// If the input is invalid, the user will be asked to enter a valid input.
    /// @param title The title of the input to be shown to the user to get input
    /// @return Returns the int input
    static int getIntInput(std::string title);

    /// @brief Splits a string into a vector of strings using the given delimiter
    static std::vector<std::string> spiltString(std::string str, char delimiter);

    /// @brief Clears the screen
    static void clearScreen();

    /// @brief Gets an input from the user (clears the screen before getting input).
    /// @param title The title of the input to be shown to the user to get input
    /// @return Returns the string input
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

    /// @brief Checks if a date is before another date
    /// @return Returns true if the first date is before the second date, false otherwise
    static bool isDateBefore(std::tm date1, std::tm date2);

    /// @brief Sorts an array using the quicksort algorithm
    /// @tparam T The type of the elements in the array
    /// @param arr The array to sort
    /// @param isLess A function that takes two elements of type T and returns true if the first element is less than the second element (it's used to compare the elements)
    /// @param min The minimum index of the array to sort (inclusive)
    /// @param max The maximum index of the array to sort (exclusive)
    template <typename T>
    static void quicksort(T *arr, std::function<bool(T, T)> isLess, int min, int max);

    /// @brief Sorts a vector using the quicksort algorithm
    /// @tparam T The type of the elements in the vector
    /// @param vec The vector to sort
    /// @param isLess A function that takes two elements of type T and returns true if the first element is less than the second element (it's used to compare the elements)
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