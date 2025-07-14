#include "channel.hpp"
Channel::Channel(Professor *_the_professor)
{
    the_professor = _the_professor;
}
void Channel::add_member(Student *the_member)
{
    members.push_back(the_member);
}
void Channel::add_ta(Student *the_ta)
{
    teacher_assistances.push_back(the_ta);
}

void Channel::add_post(string title, string message, string image_path, string author_id, string lecture_id)
{
    if (!is_an_admin(author_id))
        throw PermissionExeption();
    handle_having_this_lecture(author_id, lecture_id);
    string author_name = "";
    post_id_generator++;
    channel_posts.push_back(new Channel_post(to_string(post_id_generator), message, title, image_path, find_author_name(author_id)));
}

void Channel::send_notification(string author_id, string notif)
{
    if (the_professor->get_id() == author_id)
    {
        for (auto ta : teacher_assistances)
            ta->add_notification(notif);
        for (auto member : members)
            member->add_notification(notif);
    }
    else
    {
        for (auto ta : teacher_assistances)
        {
            if (ta->get_id() == author_id)
            {
                continue;
            }
            ta->add_notification(notif);
        }
        the_professor->add_notification(notif);
        for (auto member : members)
            member->add_notification(notif);
    }
}

bool Channel::is_an_admin(string id)
{
    if (the_professor->get_id() == id)
        return true;
    for (auto ta : teacher_assistances)
        if (ta->get_id() == id)
            return true;
    return false;
}
string Channel::find_author_name(string id)
{
    if (the_professor->get_id() == id)
        return the_professor->get_name();
    for (auto ta : teacher_assistances)
        if (ta->get_id() == id)
            return ta->get_name();
    return NULL;
}
void Channel::handle_having_this_lecture(string author_id, string lecture_id)
{
    if (the_professor->get_id() == author_id)
        the_professor->handle_having_this_lecture(lecture_id);
    for (auto ta : teacher_assistances)
        if (ta->get_id() == author_id)
        {
            ta->handle_having_this_lecture(lecture_id);
        }
}
bool Channel::is_current_user_in_channel(string current_user_id)
{
    if (the_professor->get_id() == current_user_id)
        return true;
    for (auto ta : teacher_assistances)
        if (ta->get_id() == current_user_id)
            return true;
    for (auto member : members)
        if (member->get_id() == current_user_id)
            return true;
    return false;
}

vector<string> Channel::get_channel(string current_user_id)
{
    if (!is_current_user_in_channel(current_user_id))
        throw PermissionExeption();
    vector<string> output;
    for (int i = channel_posts.size() - 1; i >= 0; i--)
    {
        output.push_back(channel_posts[i]->get_brief_detail());
    }
    return output;
}

bool Channel::is_post_in_channel_posts(string post_id)
{
    for (auto channel_post : channel_posts)
    {
        if (channel_post->get_id() == post_id)
        {
            return true;
        }
    }
    return false;
}

string Channel::get_post(string post_id, string current_user_id)
{
    if (!is_current_user_in_channel(current_user_id))
        throw PermissionExeption();
    if (!is_post_in_channel_posts(post_id))
        throw NotFoundExeption();
    vector<string> output;
    for (auto channel_post : channel_posts)
    {
        if (channel_post->get_id() == post_id)
            output = channel_post->get_complete_detail();
    }
    return output[0];
}
