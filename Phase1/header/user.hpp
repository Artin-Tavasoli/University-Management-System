#pragma once
#include "includes.hpp"
#include "course.hpp"
#include "utilities.hpp"
#include "lecture.hpp"
#include "major.hpp"
#include "not_found_error.hpp"
#include "bad_req_error.hpp"
#include "permission_error.hpp"
#include "empty_error.hpp"
#include "all_error.hpp"
#include "post.hpp"
class User
{
protected:
    string password, id , name;
    vector<Post *> posts;
    int post_id_generator = 0;
    vector<User *> connected;
    vector<string> notifications;

public:
    User(string _id, string _password);
    string get_id() { return id; }
    string get_password() { return password; }
    vector<string> get_personal_page();
    vector<string> get_post(string post_id);
    virtual string get_personal_detail_of_page() = 0;
    void add_post(string title, string message);
    void delete_post(string post_id);
    int get_post_id_generator() { return post_id_generator; }
    void add_connect(User *the_user);
    bool is_connected(string id);
    void add_notification(string notification)
    {
        notifications.push_back(notification);
    }
    vector<string> get_notification();
    

};
