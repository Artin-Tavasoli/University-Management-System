#pragma once
#include "includes.hpp"
#include "lecture.hpp"
struct Ta_applicant_info
{
    Ta_applicant_info(string _student_id, string _student_name, int _semester);
    string student_id;
    int semester;
    string student_name;
    string result;
};