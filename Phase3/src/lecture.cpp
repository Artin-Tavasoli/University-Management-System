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

string Lecture::get_personal_detail_in_html()
{
    string body = "";
    body += R"(<div class="box">)";
    body += R"(<div class="lecture-details">)";
    body += R"(<p>ID: )" + to_string(id) + R"(</p>)";
    body += R"(<p>Name: )" + the_course->name + R"(</p>)";
    body += R"(<p>Capacity: )" + to_string(capacity) + R"(</p>)";
    body += R"(<p>Professor_name: )" + professor_name + R"(</p>)";
    body += R"(<p>lecture_time: )" + lecture_time->get_time_str() + R"(</p>)";
    body += R"(<p>exam_date: )" + exam_date + R"(</p>)";
    body += R"(<p>class_number: )" + to_string(class_number) + R"(</p>)";
    body += R"(</div>)";
    body += R"(</div>)";
    return body;
}