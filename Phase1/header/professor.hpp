#pragma once
#include "user.hpp"
class Professor : public User
{
private:
    string position, major_name;
    int major_id;
    vector<Lecture *> my_lectures;
public:
    Professor(string _id, string _name, int _major_id, string _position, string _password, string _major_name);
    int get_major_id() { return major_id; }
    string get_name() { return name; }
    void add_lecture(Lecture *the_lecture);
    void handle_time_for_teaching(Time *the_time);
    string get_personal_detail_of_page();
};