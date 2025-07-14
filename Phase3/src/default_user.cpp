#include "default_user.hpp"
Default_user::Default_user(string _id, string _password)
    : User(_id, _password)
{
    name = DEFAULT_USER_NAME;
}
string Default_user::get_personal_detail_of_page()
{
    string body = "";
    body += R"(<div class="box">)";
    if (profile_photo_path != "")
        body += R"(<img src=")" + profile_photo_path + R"(" alt="Profile Photo" class="profile-photo">)";
    else
    {
        body += R"(<img src=")";
        body += R"(/unlogged_profile_pic.png" )";
        body += R"(alt="Profile Photo" class="profile-photo">)";
    }
    body += R"(<div class="user-details">)";
    body += R"(<p>ID: )" + id + R"(</p>)";
    body += R"(<p>Name: )" + name + R"(</p>)";
    body += R"(</div>)";
    body += R"(</div>)";
    return body;
    // return DEFAULT_USER_NAME;
}