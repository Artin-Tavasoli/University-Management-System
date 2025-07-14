#pragma once
#include "includes.hpp"
class Time
{
public:
    Time(int _start_time, int _finish_time, string _day);
    void handle_Interference_in_time(Time *another_time);
    string get_time_str(){ return time_str;}

private:
    string day;
    int start_time, finish_time;
    string time_str;
};