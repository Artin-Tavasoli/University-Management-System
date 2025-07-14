#pragma once
#include "includes.hpp"
#include "course.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "default_user.hpp"
#include "utilities.hpp"
#include "lecture.hpp"
#include "major.hpp"
#include "handler.hpp"
#include "not_found_error.hpp"
#include "bad_req_error.hpp"
#include "permission_error.hpp"
#include "empty_error.hpp"
#include "all_error.hpp"
#include "ta_applicant_info.hpp"
class System
{
private:
    Handler *utms_handler;

public:
    System(Handler *_handler);
    void run();
    void handle_arg_type_delimeter(const vector<string> splitted_req);
    vector<string> send_post_command(const vector<string> splitted_req);
    vector<string> send_get_command(const vector<string> splitted_req);
    vector<string> send_delete_command(const vector<string> splitted_req);
    vector<string> send_put_command(const vector<string> splitted_req);
    void print_output(vector<string> &output);
    void check_size_delete_req(const vector<string> splitted_req);
    void check_size_post_req(const vector<string> splitted_req);
    void check_size_get_req(const vector<string> splitted_req);
    vector<string> put_together_spaced_words(const vector<string> splitted_req);
    void handle_login();
    void handle_valid_post(const vector<string> splitted_req);
    void handle_valid_get(const vector<string> splitted_req);
    void handle_valid_delete(const vector<string> splitted_req);
    void get_ta_applicants_results(vector<Ta_applicant_info *> &ta_applicants_info);

    vector<string> get_login_req_data(const vector<string> splitted_req);
    vector<string> get_add_course_req_data(const vector<string> splitted_req);
    vector<string> get_get_post_req_data(const vector<string> splitted_req);
    vector<string> get_add_normal_post_req_data(const vector<string> splitted_req);
    vector<string> get_add_ta_form_post_data(const vector<string> splitted_req);
    vector<string> get_send_ta_req_data(const vector<string> splitted_req);
    vector<string> get_course_post_req_data(const vector<string> splitted_req);
    vector<string> get_get_course_post_data(const vector<string> splitted_req);
    void handle_valid_get_course(const vector<string> splitted_req);
    void handle_close_ta_form_req(const vector<string> splitted_req);
};