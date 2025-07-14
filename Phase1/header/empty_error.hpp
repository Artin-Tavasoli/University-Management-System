#pragma once
#include "includes.hpp"
#include "all_error.hpp"
class EmptyExeption : public ErrorExeption
{
public:
    EmptyExeption()
        : ErrorExeption()
        {
            message = "Empty";
        }
    void print_error();
};