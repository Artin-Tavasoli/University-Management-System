#include "lecture.hpp"
#include "channel.hpp"
struct Channel_lecture_interface
{
    Channel_lecture_interface(Channel *_the_channel, Lecture *_the_lecture)
    {
        the_lecture = _the_lecture;
        the_channel = _the_channel;
    }
    Lecture *the_lecture;
    Channel *the_channel;
};