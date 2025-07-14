#include "ta_form_post.hpp"
Ta_form::Ta_form(string _post_id, string _message, Lecture *_the_lecture)
    : Post(_post_id, _message)
{
    the_lecture = _the_lecture;
}
string Ta_form::get_brief_detail()
{
    return post_id + ta_form_brief_detail_message::FIRST_PART + the_lecture->get_name() + ta_form_brief_detail_message::SECOND_PART;
}
vector<string> Ta_form::get_complete_detail()
{
    vector<string> output;
    output.push_back(get_brief_detail());
    output.push_back(the_lecture->get_personal_detail());
    output.push_back(message);
    return output;
}
void Ta_form::add_student_id(string sid)
{
    student_ids.push_back(sid);
}
void Ta_form::handle_min_prerequisite(int student_semester)
{
    if (student_semester <= the_lecture->the_course->prerequisite)
        throw PermissionExeption();
}
