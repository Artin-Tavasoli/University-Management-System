#pragma once
#include "includes.hpp"
#include "all_error.hpp"
class BadReqExeption : public ErrorExeption
{
public:
    BadReqExeption()
        : ErrorExeption()
    {
        message = error_message::BAD_REQ;
    }
    void print_error();
};