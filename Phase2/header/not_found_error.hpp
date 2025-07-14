#pragma once
#include "includes.hpp"
#include "all_error.hpp"
class NotFoundExeption : public ErrorExeption
{
public:
    NotFoundExeption()
        : ErrorExeption()
        {
            message = error_message::NOT_FOUND;
        }
    void print_error();
};