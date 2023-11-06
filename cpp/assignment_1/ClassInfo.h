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

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include "structs.h"
#include "Student.h"

struct ClassInfo
{
public:
    map<string, int> gradeDistribution;
    int studentCount;

    ClassInfo(int studentCount, Coefficents coefficents) : studentCount(studentCount), coefficents(coefficents)
    {

        students = new Student[studentCount];

        for (int i = 0; i < studentCount; i++)
        {
            Student ogr = Student::randomStudent(i, studentCount);

            *(students + i) = ogr;

            GradeInfo gradeInfo = ogr.netGrade(coefficents);

            gradeDistribution[gradeInfo.letter]++;

            average += gradeInfo.number / studentCount;

            if (minGrade == -1 || gradeInfo.number < minGrade)
            {
                minGrade = gradeInfo.number;
            }

            if (gradeInfo.number > maxGrade)
            {
                maxGrade = gradeInfo.number;
            }
        }

        normalDistribution = getNormalDistribution(average);
    }

    ~ClassInfo()
    {
        delete[] students;
    }

    void printGradeDistribution()
    {

        printTable({"Distribution of Grades (Net Grade)", "Letter", "Number of People", "Percentage"});

        for (auto [k, v] : gradeDistribution)
        {
            float gradePercentage = (float)v / studentCount * 100;

            printTable({}, {k, to_string(v), roundedString(gradePercentage) + "%"});
        }
    }

    void printStudents()
    {

        printTable({"Students And Grades", "ID", "Name", "Year Grade", "Net Grade"});

        for (unsigned int i = 0; i < studentCount; i++)
        {

            Student student = *(students + i);

            GradeInfo netGradeInfo = student.netGrade(coefficents);

            GradeInfo yearGradeInfo = student.yearGrade(coefficents);

            printTable({}, {to_string(student.studentID + 1), student.name + " " + student.surname, yearGradeInfo.letter + " (" + roundedString(yearGradeInfo.number) + ")", netGradeInfo.letter + " (" + roundedString(netGradeInfo.number) + ")"});
        }
    }

    void printInfo()
    {
        printTable({"Class Info", "Student Count", "Year Grade Coefficent", "Min Grade", "Max Grade", "Average", "Normal Distribution"},
                   {to_string(studentCount), roundedString(coefficents.yearGrade * 100) + "%", roundedString(minGrade), roundedString(maxGrade), roundedString(average), roundedString(normalDistribution)});
    }

private:
    Student *students;
    Coefficents coefficents;

    float minGrade = -1;
    float maxGrade = -1;
    float average = 0;
    float normalDistribution = 0;

    float getNormalDistribution(float average)
    {
        float result = 0;

        for (int i = 0; i < studentCount; i++)
        {
            GradeInfo gradeInfo = (students + i)->netGrade(coefficents);
            result += pow(gradeInfo.number - average, 2);
        }

        return sqrt(result / (studentCount - 1));
    }

    string roundedString(float number)
    {
        string numString = to_string(number);
        return numString.substr(0, numString.find(".") + 3);
    }

    void printTable(vector<string> columns, vector<string> datas = {}, int width = 20, bool useTitle = true)
    {
        if (columns.size() > 0)
        {
            cout << endl;

            if (useTitle)
            {
                int rowWidth = width * (columns.size() - 1);

                int leftSide = floor((rowWidth - columns[0].size()) / 2);

                cout << setw(rowWidth) << string(leftSide - 2, '-') + "[ " + columns[0] + " ]" + string(rowWidth - columns[0].size() - leftSide - 2, '-') << endl;
            }

            for (string column : columns)
            {
                if (column == columns[0])
                {
                    continue;
                }

                cout << setw(width) << column;
            }

            cout << endl
                 << string(width * (columns.size() - 1), '-') << endl;
        }

        if (datas.size() > 0)
        {
            for (string data : datas)
            {
                cout << setw(width) << data;
            }

            cout << endl;
        }
    }
};
