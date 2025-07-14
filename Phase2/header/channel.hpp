#pragma once
#include "includes.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "channel_post.hpp"
class Channel
{
public:
    Channel(Professor *_the_professor);
    void add_member(Student *the_member);
    void add_ta(Student *the_ta);
    void add_post(string title, string message, string image_path, string author_id, string lecture_id);
    bool is_an_admin(string id);
    string find_author_name(string id);
    void send_notification(string author_id, string notif);
    void handle_having_this_lecture(string author_id, string lecture_id);
    vector<string> get_channel(string current_user_id);
    string get_post(string post_id, string current_user_id);
    bool is_current_user_in_channel(string current_user_id);
    bool is_post_in_channel_posts(string post_id);

private:
    vector<Channel_post *> channel_posts;
    vector<Student *> teacher_assistances;
    vector<Student *> members;
    Professor *the_professor;
    int post_id_generator = 0;
};