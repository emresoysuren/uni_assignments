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

#include <string>
using namespace std;

#include "structs.h"
#include "ClassInfo.h"

struct Student
{
public:
    int studentID;
    string name;
    string surname;
    float midterm;
    float assignment[2];
    float quiz[2];
    float final_exam;

    GradeInfo netGrade(Coefficents coefficents)
    {
        float grade = yearGrade(coefficents).number * coefficents.yearGrade + (1 - coefficents.yearGrade) * final_exam;

        GradeInfo gradeInfo = findLetterGrade(grade);

        gradeInfo.number = grade;

        return gradeInfo;
    }

    GradeInfo yearGrade(Coefficents coefficents)
    {
        float sumOfTheCoefficents = coefficents.quiz * 2 + coefficents.assignment * 2 + coefficents.midterm;

        float yearGrade = (assignment[0] + assignment[1]) * (coefficents.assignment / sumOfTheCoefficents) + (quiz[0] + quiz[1]) * (coefficents.quiz / sumOfTheCoefficents) + midterm * (coefficents.midterm / sumOfTheCoefficents);

        GradeInfo gradeInfo = findLetterGrade(yearGrade);

        gradeInfo.number = yearGrade;

        return gradeInfo;
    }

    static Student randomStudent(int studentID, int studentCount)
    {
        static const string names[30] = {
            "John",
            "Mary",
            "Robert",
            "Patricia",
            "Michael",
            "Jennifer",
            "William",
            "Elizabeth",
            "David",
            "Linda",
            "Richard",
            "Barbara",
            "Joseph",
            "Susan",
            "Thomas",
            "Jessica",
            "Charles",
            "Sarah",
            "Christopher",
            "Karen",
            "Daniel",
            "Nancy",
            "Matthew",
            "Lisa",
            "Anthony",
            "Betty",
            "Donald",
            "Margaret",
            "Mark",
            "Sandra",
        };

        static const string surnames[30] = {
            "Smith",
            "Johnson",
            "Williams",
            "Brown",
            "Jones",
            "Miller",
            "Davis",
            "Garcia",
            "Rodriguez",
            "Wilson",
            "Martinez",
            "Anderson",
            "Taylor",
            "Thomas",
            "Hernandez",
            "Moore",
            "Martin",
            "Jackson",
            "Thompson",
            "White",
            "Lopez",
            "Lee",
            "Gonzalez",
            "Harris",
            "Clark",
            "Lewis",
            "Robinson",
            "Walker",
            "Perez",
            "Hall",
        };

        Student student;

        student.studentID = studentID;
        student.name = names[randomNumber(0, 29)];
        student.surname = surnames[randomNumber(0, 29)];
        student.midterm = randomGrade(studentCount);
        student.quiz[0] = randomGrade(studentCount);
        student.quiz[1] = randomGrade(studentCount);
        student.assignment[0] = randomGrade(studentCount);
        student.assignment[1] = randomGrade(studentCount);
        student.final_exam = randomGrade(studentCount);

        return student;
    }

private:
    static GradeInfo findLetterGrade(float numberGrade)
    {
        const GradeInfo letterGrades[9] = {
            {"AA", 4.0, 90},
            {"BA", 3.5, 85},
            {"BB", 3.0, 80},
            {"CB", 2.5, 75},
            {"CC", 2.0, 65},
            {"DC", 1.5, 58},
            {"DD", 1.0, 50},
            {"FD", 0.5, 40},
            {"FF", 0.0, 0},
        };

        for (int i = 0; i < 9; i++)
        {
            GradeInfo gradeInfo = letterGrades[i];

            if (numberGrade >= gradeInfo.number)
            {
                return gradeInfo;
            }
        }

        throw;
    }

    static int randomNumber(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }

    static float randomGrade(int studentCount)
    {
        static float gradeDistribution[3];

        int totalExamCount = studentCount * 6;

        while (true)
        {
            switch (randomNumber(0, 2))
            {
            case 0:
                if (gradeDistribution[0] < round(totalExamCount * 0.2))
                {
                    gradeDistribution[0]++;
                    return (float)randomNumber(81, 100);
                }
                break;
            case 1:
                if (gradeDistribution[1] < totalExamCount - round(totalExamCount * 0.2) - round(totalExamCount * 0.3))
                {
                    gradeDistribution[1]++;
                    return (float)randomNumber(51, 80);
                }
                break;
            case 2:
                if (gradeDistribution[2] < round(totalExamCount * 0.3))
                {
                    gradeDistribution[2]++;
                    return (float)randomNumber(0, 50);
                }
                break;
            }
        }
    };
};
