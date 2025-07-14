#pragma once
#include "includes.hpp"
class ErrorExeption
{
public:
    ErrorExeption(){};
    void print_error(){cout<<message<<endl;};
protected:
    string message;
};