#pragma once
#include "lecture.hpp"
#include "post.hpp"
#include "not_found_error.hpp"
#include "bad_req_error.hpp"
#include "permission_error.hpp"
#include "empty_error.hpp"
#include "all_error.hpp"
class Ta_form : public Post
{
private:
    Lecture *the_lecture;
    vector<string> student_ids;

public:
    Ta_form(string _post_id, string _message, Lecture *_the_lecture);
    string get_brief_detail();
    vector<string> get_complete_detail();
    void add_student_id(string sid);
    void handle_min_prerequisite(int student_semester);
    vector<string> get_ta_applicants_id() { return student_ids; }
    string get_lecture_id(){return the_lecture->get_id();}
};