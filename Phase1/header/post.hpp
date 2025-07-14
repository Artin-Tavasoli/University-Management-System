#pragma once
#include "includes.hpp"
struct Post
{
    Post(string _post_id, string _title, string _message)
    {
        post_id = _post_id;
        title = _title;
        message = _message;
    }
    string post_id;
    string title;
    string message;
};