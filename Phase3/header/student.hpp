#pragma once
#include "user.hpp"
class Student : public User
{
private:
    int semester, major_id;
    string major_name;
    vector<Lecture *> my_lectures;
    vector<Lecture *> my_lectures_as_ta;
public:
    Student(string _id, string _name, int _major_id, int _semester, string _password, string _major_name);
    string get_personal_detail_of_page();
    void register_my_course(Lecture *the_lecture);
    void handle_Interference_in_date(Lecture *the_lecture);
    void delete_my_course(string id);
    vector<string> get_my_course();
    int get_semester() { return semester; }
    string get_name() {return name;}
    void handle_having_this_lecture(string lecture_id);
    void add_to_mylecture_as_ta(Lecture *the_lecture);
    string get_my_course_in_html();
};