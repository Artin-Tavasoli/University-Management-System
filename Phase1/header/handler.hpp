#pragma once
#include "includes.hpp"
#include "course.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "default_user.hpp"
#include "utilities.hpp"
#include "lecture.hpp"
#include "major.hpp"
#include "not_found_error.hpp"
#include "bad_req_error.hpp"
#include "permission_error.hpp"
#include "empty_error.hpp"
#include "all_error.hpp"
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
    User *current_user = NULL;

public:
    Handler(const vector<string> &_file_paths);
    void set_majors();
    void set_students();
    void set_courses();
    void set_professors();
    void set_default_user();

    bool is_id_vaild(string id);
    bool is_password_vaild(string password);
    bool is_user_logged_in();
    bool does_professor_present_course(Professor *the_professor, Course *the_course);
    Professor *find_professor(string id);
    Course *find_course(string id);
    vector<string> login(const vector<string> splitied_req);
    vector<string> logout();
    vector<string> add_course(const vector<string> splitied_req);
    vector<string> add_post(const vector<string> splitied_req);
    vector<string> add_connect(const vector<string> splitied_req);

    vector<string> get_courses(const vector<string> splitied_req);
    vector<string> get_personal_page(const vector<string> splitied_req);
    bool is_lecture_id_valid(string id);
    vector<string> get_post(const vector<string> splitied_req);
    vector<string> get_notification();
    vector<string> get_my_courses();

    vector<string> delete_post(const vector<string> splitied_req);
    vector<string> delete_course(const vector<string> splitied_req);

    vector<string> register_my_course(const vector<string> splitied_req);
};