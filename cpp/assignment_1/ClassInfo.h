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

#include "structs.h"
#include "Student.h"

/// @brief A struct that hold the information of the class
struct ClassInfo
{
public:
    /// @brief A map that hold the distribution of the grades
    std::map<std::string, int> gradeDistribution;

    /// @brief Holds the count of the students
    int studentCount;

    ClassInfo(int studentCount, Coefficents coefficents) : studentCount(studentCount), coefficents(coefficents)
    {
        // Create a new array of students with the given student count
        students = new Student[studentCount];

        // Iterate over the students array and create a new random student for each index
        for (int i = 0; i < studentCount; i++)
        {
            Student ogr = Student::randomStudent(i, studentCount);

            *(students + i) = ogr;

            // Calculate the net grade info of the student
            GradeInfo gradeInfo = ogr.netGrade(coefficents);

            // Increase the count of the letter grade that the student got
            gradeDistribution[gradeInfo.letter]++;

            // Increase the average
            average += gradeInfo.number / studentCount;

            // Check if the grade is the min or max grade
            if (minGrade == -1 || gradeInfo.number < minGrade)
            {
                minGrade = gradeInfo.number;
            }

            if (gradeInfo.number > maxGrade)
            {
                maxGrade = gradeInfo.number;
            }
        }

        // Calculate the normal distribution of the class by passing the average
        normalDistribution = getNormalDistribution(average);
    }

    /// @brief Destructor of the ClassInfo struct
    ~ClassInfo()
    {
        // Delete the students array when the ClassInfo struct is destroyed
        delete[] students;
    }

    /// @brief Prints a table that shows the distribution of the grades
    void printGradeDistribution()
    {

        printTable({"Distribution of Grades (Net Grade)", "Letter", "Number of People", "Percentage"});

        // Iterate over the gradeDistribution map and print the distribution of the grades
        for (auto [k, v] : gradeDistribution)
        {
            float gradePercentage = (float)v / studentCount * 100;

            printTable({}, {k, std::to_string(v), roundedString(gradePercentage) + "%"});
        }
    }

    /// @brief Prints a table that shows the information of the students
    void printStudents()
    {

        printTable({"Students And Grades", "ID", "Name", "Year Grade", "Net Grade"});

        // Iterate over the students array and print the information of the students
        for (unsigned int i = 0; i < studentCount; i++)
        {

            Student student = *(students + i);

            GradeInfo netGradeInfo = student.netGrade(coefficents);

            GradeInfo yearGradeInfo = student.yearGrade(coefficents);

            printTable({}, {std::to_string(student.studentID + 1), student.name + " " + student.surname, yearGradeInfo.letter + " (" + roundedString(yearGradeInfo.number) + ")", netGradeInfo.letter + " (" + roundedString(netGradeInfo.number) + ")"});
        }
    }

    /// @brief Prints a table that shows all the other information about the class
    void printInfo()
    {
        printTable({"Class Info", "Student Count", "Year G. Coefficent", "Min Grade", "Max Grade", "Average", "Normal Distribution"},
                   {std::to_string(studentCount), roundedString(coefficents.yearGrade * 100) + "%", roundedString(minGrade), roundedString(maxGrade), roundedString(average), roundedString(normalDistribution)});
    }

private:
    Student *students;
    Coefficents coefficents;

    // Class information about the grades of the students that calculated in the constructor
    float minGrade = -1;
    float maxGrade = -1;
    float average = 0;
    float normalDistribution = 0;

    /// @brief Calculates the normal distribution of the class
    /// @param average The average grade of the class to calculate the normal distribution
    /// @return Returns the normal distrubiton of the class
    float getNormalDistribution(float average)
    {
        float result = 0;

        // Iterate over the students array and calculate the normal distribution
        for (int i = 0; i < studentCount; i++)
        {
            GradeInfo gradeInfo = (students + i)->netGrade(coefficents);
            result += pow(gradeInfo.number - average, 2);
        }

        return sqrt(result / (studentCount - 1));
    }

    /// @brief Rounds the given string to 2 decimal places and returns it as a string
    /// @param number The number that will be rounded
    /// @return Returns the rounded string
    std::string roundedString(float number)
    {
        // Converts the given number to string
        std::string numString = std::to_string(number);

        // Returns the string by cutting it to 2 decimal places using substr
        return numString.substr(0, numString.find(".") + 3);
    }

    /// @brief Prints a table with the given columns and datas
    void printTable(std::vector<std::string> columns, std::vector<std::string> datas = {}, int width = 20, bool useTitle = true)
    {
        if (columns.size() > 0)
        {
            std::cout << std::endl;

            // If the useTitle is true, use the first element of the columns as the title and add line around it
            if (useTitle)
            {
                int rowWidth = width * (columns.size() - 1);

                int leftSide = floor((rowWidth - columns[0].size()) / 2);

                std::cout << std::setw(rowWidth) << std::string(leftSide - 2, '-') + "[ " + columns[0] + " ]" + std::string(rowWidth - columns[0].size() - leftSide - 2, '-') << std::endl;
            }

            // Iterate over the columns and print them with the given width
            for (std::string column : columns)
            {
                // Skip the first element of the columns if the useTitle is true
                if (column == columns[0])
                {
                    continue;
                }

                std::cout << std::setw(width) << column;
            }

            // Print a line that seperates the columns and the datas
            std::cout << std::endl
                      << std::string(width * (columns.size() - 1), '-') << std::endl;
        }

        // If provided print the datas
        if (datas.size() > 0)
        {
            // Iterate over the datas and print them with the given width
            for (std::string data : datas)
            {
                std::cout << std::setw(width) << data;
            }

            std::cout << std::endl;
        }
    }
};
