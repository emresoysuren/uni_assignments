/****************************************************************************
**					          SAKARYA UNIVERSITY
**			        COMPUTER AND INFORMATION SCIENCES FACULTY
**				        COMPUTER ENGINEERING DEPARTMENT
**				          INTRODUCTION TO PROGRAMMING
**
**				        ASSIGNMENT NO.: 1
**				        STUDENT NAME..: Emre Soysüren
**				        STUDENT ID....: G221210049
**				        GROUP.........: 2. Education / C Group
****************************************************************************/

#include <iostream>
#include <cmath>
#include <regex>
using namespace std;

#include "ClassInfo.h"
#include "structs.h"

template <typename T>
void getNumber(T *, string = "");

int main()
{
    // Align the output to the left
    cout << left;

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Take the coefficents and student count from the user
    Coefficents coefficents;

    int studentCount;

    getNumber(&coefficents.assignment, "Define the coefficents of the assignmets: ");

    getNumber(&coefficents.quiz, "Define the coefficents of the quizzes: ");

    getNumber(&coefficents.midterm, "Define the coefficent of the midterm exam: ");

    // Get the year grade coefficent from the user in a block so that the variable will be destroyed after the block
    {
        float yearGradeCoefficent;

        getNumber(&yearGradeCoefficent, "Define the coefficent of the year grade: ");

        // Always keep the year grade coefficent between 0 and 1
        // To do that we are using the log10 function to get the number of digits in the number
        // and we're creating a new number that's 10^(number of digits in the number + 1).
        yearGradeCoefficent = yearGradeCoefficent / pow(10, ceil(log10(yearGradeCoefficent)));

        coefficents.yearGrade = yearGradeCoefficent;
    }

    getNumber(&studentCount, "Define student count: ");

    // Create a new ClassInfo struct with the given coefficents and student count
    ClassInfo classInfo(studentCount, coefficents);

    // Print the information about the class

    classInfo.printStudents();

    classInfo.printGradeDistribution();

    classInfo.printInfo();

    // Indicate the end of the program
    cout << "\nEnd of the Program" << endl;

    return 0;
}

/// @brief Get a number from the user and assign it to the given pointer
/// @tparam T The type of the number
/// @param ptr The pointer to assign the number to
/// @param message The message to display to the user
template <typename T>
void getNumber(T *ptr, string message)
{
    string input;

    // Display the message
    cout << "\033[34m" << message << "\033[0m";

    // Get the input from the user
    cin >> input;

    // Create a regex to check if the input is a number including decimals
    regex onlyNumbers("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$");

    if (!regex_match(input, onlyNumbers))
    {
        cout << "\033[31m"
             << "Given input is not a number. Please try again."
             << "\033[0m" << endl
             << endl;

        // Recursively call the function until the user enters a valid number
        return getNumber(ptr, message);
    }

    // Convert the input to a number and assign it to the given pointer
    *ptr = (T)stof(input);
}
