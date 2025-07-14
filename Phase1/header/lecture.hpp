#pragma once
#include "includes.hpp"
#include "course.hpp"
#include "time.hpp"
struct Lecture
{
   Lecture(Course* _the_course, string _professor_id, int _capacity,Time *_lecture_time , string _exam_date, int _class_number, int _id, string _professor_name);
    Course *the_course;
    string professor_id;
    string professor_name;
    int capacity;
    string exam_date;
    int class_number;
    int id;
    Time *lecture_time;
};
