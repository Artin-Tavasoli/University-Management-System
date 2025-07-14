#include "student.hpp"
Student::Student(string _id, string _name, int _major_id, int _semester, string _password, string _major_name)
    : User(_id, _password)
{
    semester = _semester;
    name = _name;
    major_id = _major_id;
    major_name = _major_name;
}

string Student::get_personal_detail_of_page()
{
    string space = " ";
    string personal_info = name + space + major_name + space + to_string(semester) + space;
    for (auto my_lecture : my_lectures)
    {
        personal_info += my_lecture->the_course->name + ",";
    }
    personal_info.erase(personal_info.size() - 1);
    return personal_info;
}

void Student::register_my_course(Lecture *the_lecture)
{
    if (semester < the_lecture->the_course->prerequisite)
    {
        throw PermissionExeption();
    }
    bool major_legible_for_register = false;
    for (auto lecture_major_id : the_lecture->the_course->majors_id)
    {
        if (lecture_major_id == major_id)
        {
            major_legible_for_register = true;
        }
    }
    if (!major_legible_for_register)
        throw PermissionExeption();
    for(auto lecture : my_lectures)
    {
        lecture->lecture_time->handle_Interference_in_time(the_lecture->lecture_time);
    }
    handle_Interference_in_date(the_lecture);
    my_lectures.push_back(the_lecture);
    for (auto user : connected)
    {
        user->add_notification(id + " " + name + ":" + " " + GET_LECTURE_NOTIFICATION);
    }
}

void Student::handle_Interference_in_date(Lecture *the_lecture)
{
    for (auto lecture : my_lectures)
    {
        if (the_lecture->exam_date == lecture->exam_date)
            throw PermissionExeption();
    }
}

void Student::delete_my_course(string course_id)
{
    int index_to_be_deleted = 0;
    bool find_id = false;
    for (int i = 0; i < my_lectures.size(); i++)
    {
        if (to_string(my_lectures[i]->id) == course_id)
        {
            index_to_be_deleted = i;
            find_id = true;
        }
    }
    if (!find_id)
        throw NotFoundExeption();
    my_lectures.erase(my_lectures.begin() + index_to_be_deleted);
    for (auto user : connected)
    {
        user->add_notification(id + " " + name + ":" + " " + DELETE_LECTURE_NOTIFICATION);
    }
}

vector<string> Student::get_my_course()
{
    vector<string> output;
    if (my_lectures.empty())
        throw EmptyExeption();
    for (auto my_lecture : my_lectures)
    {
        output.push_back(to_string(my_lecture->id) + " " + my_lecture->the_course->name + " " + to_string(my_lecture->capacity) + " " + my_lecture->professor_name + " " + my_lecture->lecture_time->get_time_str() + " " + my_lecture->exam_date + " " + to_string(my_lecture->class_number));
    }
    return output;
}
