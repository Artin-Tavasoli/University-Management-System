#pragma once
#include "includes.hpp"
#include "../server/server.hpp"
class ErrorExeption
{
public:
    ErrorExeption(){};
    void print_error() { cout << message << endl; };
    string get_message() { return message; }
    Response *generate_error_response();
    string readHtmlFile(const string &filePath);
protected:
    string message;
};