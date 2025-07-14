#pragma once
#include "includes.hpp"
#include "all_error.hpp"
class PermissionExeption : public ErrorExeption
{
public:
    PermissionExeption()
        : ErrorExeption()
        {
            message = error_message::PERMISSION_DENIED;
        }
    void print_error();
};