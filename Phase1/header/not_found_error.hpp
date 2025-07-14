#pragma once
#include "includes.hpp"
#include "all_error.hpp"
class NotFoundExeption : public ErrorExeption
{
public:
    NotFoundExeption()
        : ErrorExeption()
        {
            message = "Not Found";
        }
    void print_error();
};