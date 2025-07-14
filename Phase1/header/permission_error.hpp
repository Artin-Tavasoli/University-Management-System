#pragma once
#include "includes.hpp"
#include "all_error.hpp"
class PermissionExeption : public ErrorExeption
{
public:
    PermissionExeption()
        : ErrorExeption()
        {
            message = "Permission Denied";
        }
    void print_error();
};