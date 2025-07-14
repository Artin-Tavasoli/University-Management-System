#pragma once
#include "includes.hpp"
vector<string> read_from_file_line_by_line(const string path);
vector<string> split(string original_command, const char delimeter);
bool is_natural_number(string str);
