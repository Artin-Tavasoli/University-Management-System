#pragma once
#include "includes.hpp"
#include "course.hpp"
#include "time.hpp"
class Lecture
{
public:
    Lecture(Course *_the_course, string _professor_id, int _capacity, Time *_lecture_time, string _exam_date, int _class_number, int _id, string _professor_name);
    bool is_lecture_id_equal(string id);
    string get_personal_detail();
    string get_brief_detail();
    string get_professor_initials() { return professor_id + " " + professor_name; }
    string get_name() { return the_course->name; }
    string get_id() { return to_string(id); }
    Course *the_course;
    Time *lecture_time;
    string exam_date;

private:
    string professor_id;
    string professor_name;
    int capacity;
    int class_number;
    int id;
};
