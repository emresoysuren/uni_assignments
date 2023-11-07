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
using namespace std;

#include "ClassInfo.h"
#include "structs.h"

int main()
{

    //  Align the output to the left
    cout << left;

    //  Seed the random number generator
    srand((unsigned int)time(NULL));

    // Take the coefficents and student count from the user
    Coefficents coefficents;

    int studentCount;

    cout << "Define the coefficents of the assignmets: ";
    cin >> coefficents.assignment;

    cout << "Define the coefficents of the quizzes: ";
    cin >> coefficents.quiz;

    cout << "Define the coefficent of the midterm exam: ";
    cin >> coefficents.midterm;

    cout << "Define the coefficent of the year grade: ";

    {
        float yearGradeCoefficent;

        cin >> yearGradeCoefficent;

        // Always keep the year grade coefficent between 0 and 1
        yearGradeCoefficent = yearGradeCoefficent / pow(10, ceil(log10(yearGradeCoefficent)));

        coefficents.yearGrade = yearGradeCoefficent;
    }

    cout << "Define student count: ";
    cin >> studentCount;

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
