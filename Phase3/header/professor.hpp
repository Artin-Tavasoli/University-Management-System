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
    void add_ta_form_post(string lecture_name, string message);
    Post *get_ta_post_from(string _id);
    void handle_ta_req_from(string student_id, string form_id, int student_semester);
    vector<string> get_ta_applicants_id(string form_id);
    string get_lecture_id_by(string form_id);
    void handle_having_this_lecture(string lecture_id);
};