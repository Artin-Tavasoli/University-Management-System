#pragma once
#include "includes.hpp"
#include "all_error.hpp"
class EmptyExeption : public ErrorExeption
{
public:
    EmptyExeption()
        : ErrorExeption()
        {
            message = error_message::EMPTY;
        }
    void print_error();
};