#pragma once
#include "user.hpp"
class Default_user : public User
{
private:
public:
    Default_user(string _id, string _password);
    string get_personal_detail_of_page();
};