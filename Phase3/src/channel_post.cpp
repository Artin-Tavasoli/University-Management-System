#include "channel_post.hpp"
Channel_post::Channel_post(string _post_id, string _message, string _title, string _image, string _author_name)
    : Post(_post_id, _message)
{
    image = _image;
    author_name = _author_name;
    title = _title;
}
string Channel_post::get_brief_detail()
{
    return post_id + " " + author_name + " " + title;
}

vector<string> Channel_post::get_complete_detail()
{
    return {get_brief_detail() + " " + message};
}