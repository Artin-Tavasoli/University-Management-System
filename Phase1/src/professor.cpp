#include "professor.hpp"
Professor::Professor(string _id, string _name, int _major_id, string _position, string _password, string _major_name)
    : User(_id, _password)
{
    name = _name;
    major_id = _major_id;
    position = _position;
    major_name = _major_name;
}
void Professor::add_lecture(Lecture *the_lecture)
{
    my_lectures.push_back(the_lecture);
}
void Professor::handle_time_for_teaching(Time *the_time)
{
    for (auto lecture : my_lectures)
    {
        lecture->lecture_time->handle_Interference_in_time(the_time);
    }
}

string Professor::get_personal_detail_of_page()
{
    string space = " ";
    string personal_info = name + space + major_name + space + position + space;
    for (auto my_lecture : my_lectures)
    {
        personal_info += my_lecture->the_course->name + ",";
    }
    personal_info.erase(personal_info.size() - 1);
    return personal_info;
}