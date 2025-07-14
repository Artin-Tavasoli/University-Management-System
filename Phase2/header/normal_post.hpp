#pragma once
#include "post.hpp"
class Normal : public Post
{
private:
    string title;
    string image_path;
public:
    Normal(string _post_id,string _message,string _title, string _image_path);
    string get_brief_detail();
    vector<string> get_complete_detail();

};