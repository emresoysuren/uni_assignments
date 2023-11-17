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

/// @brief A struct that holds the information of the grades
struct GradeInfo
{
    std::string letter;
    float coefficent;
    float number;
};

/// @brief A struct that holds the information of the coefficents of the exams
struct Coefficents
{
    float assignment;
    float quiz;
    float midterm;
    float yearGrade;
};
