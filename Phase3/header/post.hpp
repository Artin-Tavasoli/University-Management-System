#pragma once
#include "includes.hpp"
#include "lecture.hpp"
class Post
{
public:
    Post(string _post_id, string _message);
    virtual string get_brief_detail() = 0;
    virtual vector<string> get_complete_detail() = 0;
    bool is_post_id_equal(string id);
    string get_id(){return post_id;}
protected:
    string post_id;
    string message;
};