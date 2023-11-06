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

    cout << left;

    srand((unsigned int)time(NULL));

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

        yearGradeCoefficent = yearGradeCoefficent / pow(10, ceil(log10(yearGradeCoefficent)));

        coefficents.yearGrade = yearGradeCoefficent;
    }

    cout << "Define student count: ";
    cin >> studentCount;

    ClassInfo classInfo(studentCount, coefficents);

    classInfo.printStudents();

    classInfo.printGradeDistribution();

    classInfo.printInfo();

    cout << "\nEnd of the Program" << endl;

    return 0;
}
