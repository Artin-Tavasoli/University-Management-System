#include "normal_post.hpp"
Normal::Normal(string _post_id, string _message, string _title, string _image_path)
    : Post(_post_id, _message)
{
    title = _title;
    image_path = _image_path;
}
string Normal::get_brief_detail()
{
    return post_id + " " + title;
}
vector<string> Normal::get_complete_detail()
{
    return {get_brief_detail() + " " + message};
}
