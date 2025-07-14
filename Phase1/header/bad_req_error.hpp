#pragma once
#include "includes.hpp"
#include "all_error.hpp"
class BadReqExeption : public ErrorExeption
{
public:
    BadReqExeption()
        : ErrorExeption()
        {
            message = "Bad Request";
        }
    void print_error();
};