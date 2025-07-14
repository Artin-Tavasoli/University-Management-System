#pragma once
#include "lecture.hpp"
#include "post.hpp"
#include "not_found_error.hpp"
#include "bad_req_error.hpp"
#include "permission_error.hpp"
#include "empty_error.hpp"
#include "all_error.hpp"
class Channel_post : public Post
{
private:
    string image;
    string author_name;
    string title;

public:
    Channel_post(string _post_id, string _message, string title, string _image, string _author_id);
    string get_brief_detail();
    vector<string> get_complete_detail();
};