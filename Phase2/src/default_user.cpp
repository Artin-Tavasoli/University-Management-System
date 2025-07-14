#include "default_user.hpp"
Default_user::Default_user(string _id, string _password)
    : User(_id, _password)
{
    name = DEFAULT_USER_NAME;
}
string Default_user::get_personal_detail_of_page()
{
    return DEFAULT_USER_NAME;
}