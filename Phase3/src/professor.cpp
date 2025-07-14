#include "professor.hpp"
Professor::Professor(string _id, string _name, int _major_id, string _position, string _password, string _major_name)
    : User(_id, _password)
{
    name = _name;
    major_id = _major_id;
    position = _position;
    major_name = _major_name;
}
void Professor::add_lecture(Lecture *the_lecture)
{
    my_lectures.push_back(the_lecture);
}
void Professor::handle_time_for_teaching(Time *the_time)
{
    for (auto lecture : my_lectures)
    {
        lecture->lecture_time->handle_Interference_in_time(the_time);
    }
}

string Professor::get_personal_detail_of_page()
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
    body += R"(<p>Major: )" + major_name + R"(</p>)";
    body += R"(<p>Position: )" + position + R"(</p>)";
    body += R"(</div>)";
    body += R"(</div>)";
    // string space = " ";
    // string personal_info = name + space + major_name + space + to_string(semester) + space;
    // for (auto my_lecture : my_lectures)
    // {
    //     personal_info += my_lecture->the_course->name + ",";
    // }
    // personal_info.erase(personal_info.size() - 1);
    // return personal_info;
    return body;
    // string personal_info = name + space + major_name + space + position + space;
    // for (auto my_lecture : my_lectures)
    // {
    //     personal_info += my_lecture->the_course->name + ",";
    // }
    // personal_info.erase(personal_info.size() - 1);
    // return personal_info;
}
void Professor::add_ta_form_post(string _id, string message)
{
    string lecture_name;
    bool found_lecture = false;
    Lecture *the_lecture;
    for (auto my_lecture : my_lectures)
        if (my_lecture->is_lecture_id_equal(_id))
        {
            found_lecture = true;
            the_lecture = my_lecture;
        }
    if (found_lecture == false)
        throw PermissionExeption();
    post_id_generator++;
    Post *the_post = new Ta_form(to_string(post_id_generator), message, the_lecture);
    for (auto user : connected)
    {
        user->add_notification(id + " " + name + ":" + " " + ADDED_TA_FORM_POST_NOTIFICATION_MESSAGE);
    }
    posts.push_back(the_post);
}

Post *Professor::get_ta_post_from(string _id)
{
    Ta_form *the_ta_form = NULL;
    for (auto post : posts)
    {
        if (_id == post->get_id())
        {
            the_ta_form = dynamic_cast<Ta_form *>(post);
            break;
        }
    }
    return the_ta_form;
}

void Professor::handle_ta_req_from(string student_id, string form_id, int student_semester)
{
    Ta_form *the_ta_form = dynamic_cast<Ta_form *>(get_ta_post_from(form_id));
    if (!the_ta_form)
        throw NotFoundExeption();
    the_ta_form->handle_min_prerequisite(student_semester);
    the_ta_form->add_student_id(student_id);
}
vector<string> Professor::get_ta_applicants_id(string form_id)
{
    Ta_form *the_ta_form = dynamic_cast<Ta_form *>(get_ta_post_from(form_id));
    if (!the_ta_form)
        throw NotFoundExeption();
    return the_ta_form->get_ta_applicants_id();
}
string Professor::get_lecture_id_by(string form_id)
{
    Ta_form *the_ta_form = dynamic_cast<Ta_form *>(get_ta_post_from(form_id));
    if (!the_ta_form)
        throw NotFoundExeption();
    return the_ta_form->get_lecture_id();
}
void Professor::handle_having_this_lecture(string lecture_id)
{
    bool found_lecture = false;
    for (auto my_lecture : my_lectures)
    {
        if (my_lecture->get_id() == lecture_id)
            found_lecture = true;
    }
    if (!found_lecture)
        throw PermissionExeption();
}