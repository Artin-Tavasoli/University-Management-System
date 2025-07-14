#pragma once
#include "includes.hpp"
struct Course
{
    Course(int _id, string _name, int _credit, int _prerequisite, vector<int> _majors_id);
    int id, credit, prerequisite;
    string name;
    vector<int> majors_id;
};