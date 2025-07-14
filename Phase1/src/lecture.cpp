#include "lecture.hpp"
Lecture::Lecture(Course* _the_course, string _professor_id, int _capacity,Time *_lecture_time , string _exam_date, int _class_number, int _id, string _professor_name)
{
    the_course = _the_course;
    professor_id = _professor_id;
    capacity = _capacity;
    exam_date = _exam_date;
    class_number = _class_number;
    id = _id;
    professor_name = _professor_name;
    lecture_time = _lecture_time;
}

