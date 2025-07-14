#include "time.hpp"
#include "not_found_error.hpp"
#include "bad_req_error.hpp"
#include "permission_error.hpp"
#include "empty_error.hpp"
#include "all_error.hpp"

Time::Time(int _start_time, int _finish_time, string _day)
{
    day = _day;
    start_time = _start_time;
    finish_time = _finish_time;
    time_str = day + ":" + to_string(start_time) + "-" + to_string(finish_time);
}

void Time::handle_Interference_in_time(Time *another_time)
{
    if (day == another_time->day)
    {
        if (start_time <= another_time->start_time && finish_time > another_time->start_time)
            throw PermissionExeption();
        if (start_time >= another_time->start_time && start_time < another_time->finish_time)
            throw PermissionExeption();
    }
}