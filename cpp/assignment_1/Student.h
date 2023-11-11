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

/// @brief A struct that hold the information of a student
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

    /// @brief Calculates the net grade of the student using the year grade, the final exam and the year grade coefficent.
    /// @param coefficents The coefficents of the grades
    /// @return The net grade of the student
    GradeInfo netGrade(Coefficents coefficents)
    {
        float grade = yearGrade(coefficents).number * coefficents.yearGrade + (1 - coefficents.yearGrade) * final_exam;

        GradeInfo gradeInfo = findLetterGrade(grade);

        gradeInfo.number = grade;

        return gradeInfo;
    }

    /// @brief Calculates the year grade of the student using the assignment, quiz and midterm grades.
    /// @param coefficents The coefficents of the grades
    /// @return The year grade of the student
    GradeInfo yearGrade(Coefficents coefficents)
    {
        float sumOfTheCoefficents = coefficents.quiz * 2 + coefficents.assignment * 2 + coefficents.midterm;

        float yearGrade = (assignment[0] + assignment[1]) * (coefficents.assignment / sumOfTheCoefficents) + (quiz[0] + quiz[1]) * (coefficents.quiz / sumOfTheCoefficents) + midterm * (coefficents.midterm / sumOfTheCoefficents);

        GradeInfo gradeInfo = findLetterGrade(yearGrade);

        gradeInfo.number = yearGrade;

        return gradeInfo;
    }

    /// @brief Create a new student with random values
    /// @param studentID The ID of the student
    /// @param studentCount The count of the students in the class to calculate the total number of the exams
    /// @return The new student with random values
    static Student randomStudent(int studentID, int studentCount)
    {
        // The names and surnames that will be used to create the random student

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

        // Creates a new student with the given studentID and random values (name, surname, grades)

        Student student;

        student.studentID = studentID;

        // Uses one of the names and surnames randomly
        student.name = names[randomNumber(0, 29)];
        student.surname = surnames[randomNumber(0, 29)];

        // Uses the randomGrade function to create random grades
        student.midterm = randomGrade(studentCount);
        student.quiz[0] = randomGrade(studentCount);
        student.quiz[1] = randomGrade(studentCount);
        student.assignment[0] = randomGrade(studentCount);
        student.assignment[1] = randomGrade(studentCount);
        student.final_exam = randomGrade(studentCount);

        return student;
    }

private:
    /// @brief Finds the matching letter grade for the given number grade
    /// @param numberGrade The number grade that will be used to find the letter grade
    /// @return The matching letter grade
    static GradeInfo findLetterGrade(float numberGrade)
    {
        // The letter grades and their minimum number grades to get that letter grade
        static const GradeInfo letterGrades[9] = {
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

        // Iterate over the letterGrades array and find the matching letter grade
        // by checking if the number grade is bigger than the minimum number grade.
        // Starts from the biggest number grade to the smallest number grade.
        // Therefore it will return the biggest letter grade that satisfies the condition.
        for (int i = 0; i < 9; i++)
        {
            GradeInfo gradeInfo = letterGrades[i];

            if (numberGrade >= gradeInfo.number)
            {
                return gradeInfo;
            }
        }

        // If the number grade couldn't find a matching letter grade, throw an exception
        // This can only happen if the given number grade is not between right constraints
        throw;
    }

    /// @brief Generates a random number between the given min and max values
    static int randomNumber(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }

    /// @brief Generates a random grade using the student count to calculate the total number of the exams
    /// @param studentCount The count of the students in the class to calculate the total number of the exams
    /// @return Returns a random grade
    static float randomGrade(int studentCount)
    {
        // A map to store the grade distribution as three different parts
        // The first part is the number of the students that got a grade between 81 and 100 and it is 20% of the total number of the exams
        // The second part is the number of the students that got a grade between 51 and 80 and it is 50% of the total number of the exams
        // The third part is the number of the students that got a grade between 0 and 50 and it is 30% of the total number of the exams
        static float gradeDistribution[3];

        // The total number of the exams is 6 times the student count
        int totalExamCount = studentCount * 6;

        // Loop until a random grade is found
        // Because it will try to find a grade that is available in the grade distribution
        while (true)
        {
            // Generate a random number between 0 and 2 to select one of the three parts of the grade distribution
            // A random grades will be only used if it is available in the selected part of the grade distribution
            switch (randomNumber(0, 2))
            {
            // If it is 0, it means that the grade will be between 81 and 100
            case 0:
                if (gradeDistribution[0] < round(totalExamCount * 0.2))
                {
                    gradeDistribution[0]++;
                    return (float)randomNumber(81, 100);
                }
                break;
            // If it is 1, it means that the grade will be between 51 and 80
            case 1:
                if (gradeDistribution[1] < totalExamCount - round(totalExamCount * 0.2) - round(totalExamCount * 0.3))
                {
                    gradeDistribution[1]++;
                    return (float)randomNumber(51, 80);
                }
                break;
            // If it is 2, it means that the grade will be between 0 and 50
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
