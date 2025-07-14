#include "user.hpp"
User::User(string _id, string _password)
{
    id = _id;
    password = _password;
}
vector<string> User::get_personal_page()
{
    vector<string> output;
    output.push_back(get_personal_detail_of_page());
    if(posts.empty())
        return output;
    for (int i = posts.size() - 1; i >= 0; i--)
    {
        output.push_back(posts[i]->post_id + " " + posts[i]->title);
    }
    return output;
}

vector<string> User::get_post(string post_id)
{
    vector<string> output;
    for (auto post : posts)
    {
        if (post->post_id == post_id)
        {
            output.push_back(get_personal_detail_of_page());
            output.push_back(post->post_id + " " + post->title + " " + post->message);
        }
    }
    return output;
}

void User::add_post(string title, string message)
{
    post_id_generator++;
    Post *the_post = new Post(to_string(post_id_generator), title, message);
    for(auto user : connected)
    {
        user->add_notification(id + " " + name +":"+ " " + ADDED_POST_NOTIFICATION_MESSAGE);
    }
    posts.push_back(the_post);
}

void User::delete_post(string post_id)
{
    bool post_id_valid = false;
    int index_to_be_erased = 0;
    for (int i = 0; i < posts.size(); i++)
    {
        if (post_id == posts[i]->post_id)
        {
            post_id_valid = true;
            index_to_be_erased = i;
        }
    }
    if (!post_id_valid)
        throw NotFoundExeption();
    Post *post_to_be_deleted = posts[index_to_be_erased];
    posts.erase(posts.begin() + index_to_be_erased);
    delete post_to_be_deleted;
}

bool User::is_connected(string id)
{
    for (int i = 0; i < connected.size(); i++)
    {
        if (connected[i]->get_id() == id)
        {   
            return true;
        }
    }
    return false;
}

void User::add_connect(User *the_user)
{
    connected.push_back(the_user);
}

vector<string> User::get_notification()
{
    vector<string> output;
    if(notifications.empty())
        throw EmptyExeption();
    for(int i = notifications.size() - 1; i >=0; i--)
    {
        output.push_back(notifications[i]);
    }
    notifications.clear();
    return output;
}