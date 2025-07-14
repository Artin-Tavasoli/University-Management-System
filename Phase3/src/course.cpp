#include "course.hpp"
Course::Course(int _id, string _name, int _credit, int _prerequisite, vector<int> _majors_id)
{
    id = _id;
    name = _name;
    credit = _credit;
    prerequisite = _prerequisite;
    majors_id = _majors_id;
}