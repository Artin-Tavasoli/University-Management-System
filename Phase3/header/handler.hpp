#pragma once
#include "includes.hpp"
#include "course.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "default_user.hpp"
#include "utilities.hpp"
#include "lecture.hpp"
#include "channel.hpp"
#include "major.hpp"
#include "not_found_error.hpp"
#include "bad_req_error.hpp"
#include "permission_error.hpp"
#include "empty_error.hpp"
#include "all_error.hpp"
#include "ta_applicant_info.hpp"
#include "channel_lecture_interface.hpp"
class Handler
{
private:
    int lecture_id_generator = 0;
    vector<string> file_paths;
    vector<Course *> courses;
    vector<Student *> students;
    vector<Professor *> professors;
    Default_user *default_user;
    vector<User *> users;
    vector<Major *> majors;
    vector<Lecture *> lectures;
    vector<Channel_lecture_interface *> channel_lecture_interfaces;
    User *current_user = NULL;

public:
    Handler(const vector<string> &_file_paths);
    void set_majors();
    void set_students();
    void set_courses();
    void set_professors();
    void set_default_user();
    void set_current_user(string _id);

    string get_current_user_post_id_gen()
    {
        return to_string(current_user->get_post_id_generator());
    }
    string get_current_user_name()
    {
        return current_user->get_name();
    }
    string get_current_user_profile_pic()
    {
        return current_user->get_profile_path();
    }
    bool is_id_vaild(string id);
    bool is_password_vaild(string password);
    bool is_user_logged_in();
    bool does_professor_present_course(Professor *the_professor, Course *the_course);
    Professor *find_professor(string id);
    Course *find_course(string id);
    Lecture *find_lecture(string id);
    Student *find_student(string id);
    void fill_ta_applicant_infos(vector<string> student_ids, vector<Ta_applicant_info *> &ta_applicants_info);
    void handle_ta_results(const vector<Ta_applicant_info *> ta_applicants_info, string fid);
    void handle_accepted_result(Ta_applicant_info *ta_applicant_info, string fid);
    void send_ta_result_notification(Ta_applicant_info *ta_applicant_info, string fid);
    string find_lecture_id_from_post_form(string fid);

    vector<string> login(string id, string password);
    vector<string> logout();
    vector<string> add_course(string course_id, string pid, string class_number, string time, string exam_date, string capacity);
    vector<string> add_normal_post(string title, string message, string image_path);
    vector<string> add_ta_form_post(string lecture_id, string message);
    vector<string> add_connect(string id);
    vector<string> send_ta_req(string pid, string form_id);
    vector<Ta_applicant_info *> close_ta_form_req(string fid);
    vector<string> add_profile_photo(string photo_path);
    vector<string> add_course_post(string id, string title, string message, string image_path);

    vector<string> get_courses(const vector<string> splitted_req);
    vector<string> get_personal_page(string id);
    bool is_lecture_id_valid(string id);
    vector<string> get_post(string id, string post_id);
    vector<string> get_notification();
    vector<string> get_my_courses();
    vector<string> get_course_channel(string id);
    vector<string> get_course_post(string lecture_id, string post_id);

    vector<string> delete_post(string id);
    vector<string> delete_course(string id);

    vector<string> register_my_course(string id);
    string get_detail_in_html(string id);
    string get_current_user_id() { return current_user->get_id(); }
    void set_profile_picture(string image_path);
    string get_courses_in_html();
    string get_my_courses_in_html();
    bool is_current_user_a_student();
};