#include "lecture.hpp"
Lecture::Lecture(Course *_the_course, string _professor_id, int _capacity, Time *_lecture_time, string _exam_date, int _class_number, int _id, string _professor_name)
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
bool Lecture::is_lecture_id_equal(string _id)
{
    if (to_string(id) == _id)
        return true;
    return false;
}
string Lecture::get_personal_detail()
{
    return to_string(id) + " " + the_course->name + " " + to_string(capacity) + " " + professor_name + " " + lecture_time->get_time_str() + " " + exam_date + " " + to_string(class_number);
}
string Lecture::get_brief_detail()
{
    return to_string(id) + " " + the_course->name + " " + to_string(capacity) + " " + professor_name;
}