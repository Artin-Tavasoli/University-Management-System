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
string Normal::get_detail_in_html()
{
    string body = "";

    body += R"(<div class="box">)";
    body += R"(<h2>Post</h2>)";
    if (image_path != "")
        body += R"(<img src=")" + image_path + R"(" alt="Profile Photo" class="post-pic">)";
    body += R"(<h3>)" + title + R"(</h3>)";
    body += R"(<p>)" + message + R"(</p>)";
    body += R"(</div>)";
    return body;
}
vector<string> Normal::get_complete_detail()
{
    return {get_brief_detail() + " " + message};
}
