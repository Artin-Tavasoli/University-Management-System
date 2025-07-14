#include "post.hpp"
Post::Post(string _post_id, string _message)
{
    post_id = _post_id;
    message = _message;
}
bool Post::is_post_id_equal(string id)
{
    if (post_id == id)
        return true;
    return false;
}