#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <algorithm>
using namespace std;

const string ERROR_MESSAGE_OPEN_FILE = "cant open the file";

const char DIFFERENT_TYPE_DELIMETER = ',';
const char SAME_TYPE_DELIMETER = ';';
const char BETWEEN_COMMAND_DELIMETER = ' ';
const string COMMAND_ARG_AND_TYPE_DELIMETER = "?";

const string GET_COMMAND = "GET";
const string PUT_COMMAND = "PUT";
const string POST_COMMAND = "POST";
const string DELETE_COMMAND = "DELETE";

const string LOGIN_REQ = "login";
const string LOGOUT_REQ = "logout";
const string COURSES_REQ = "courses";
const string NORMAL_POST_REQ = "post";
const string TA_FORM_POST_REQ = "ta_form";
const string COURSE_POST_REQ = "course_post";
const string PERSONAL_PAGE_REQ = "personal_page";
const string CONNECT_REQ = "connect";
const string NOTIFFICATION_REQ = "notification";
const string COURSE_OFFER_REQ = "course_offer";
const string My_COURSES_REQ = "my_courses";
const string TA_REQ = "ta_request";
const string CLOSE_TA_FORM_REQ = "close_ta_form";
const string PROFILE_PHOTO_REQ = "profile_photo";
const string GET_COURSE_CHANNEL_REQ = "course_channel";
const string GET_COURSE_POST_REQ = "course_post";

const string DEFAULT_USER_ID = "0";
const string DEFAULT_USER_NAME = "UT_account";
const string DEFAULT_USER_PASSWORD = "UT_account";

const string SUCCESSFULLY_FINISHED_REQ_MESSAGE = "OK";
const string ADDED_LECTURE_NOTIFICATION_MESSAGE = "New Course Offering";
const string ADDED_NORMAL_POST_NOTIFICATION_MESSAGE = "New Post";
const string ADDED_TA_FORM_POST_NOTIFICATION_MESSAGE = "New Form";
const string GET_LECTURE_NOTIFICATION = "Get Course";
const string DELETE_LECTURE_NOTIFICATION = "Delete Course";
const string ACCEPTED_RESULT_TA_REQ_NOTIFICATION = "Your request to be a teaching assistant has been accepted.";
const string REJECTED_RESULT_TA_REQ_NOTIFICATION = "Your request to be a teaching assistant has been rejected.";
const string ADDED_COURSE_POST_NOTIFICATION = "New Course Post";

const int MAJORS_PATH_NUM = 0;
const int STUDENTS_PATH_NUM = 1;
const int COURSES_PATH_NUM = 2;
const int PROFESSORS_PATH_NUM = 3;

const int LOGIN_SIZE_REQ = 7;
const int LOGOUT_SIZE_REQ = 3;
const int CONNECT_SIZE_REQ = 5;
const int COURSE_OFFER_SIZE_REQ = 15;
const int NORMAL_POST_WITHOUT_IMAGE_SIZE_REQ = 7;
const int NORMAL_POST_WITH_IMAGE_SIZE_REQ = 9;
const int TA_FORM_POST_SIZE_REQ = 7;
const int COURSE_POST_WITHOUT_IMAGE_SIZE_REQ = 9;
const int COURSE_POST_WITH_IMAGE_SIZE_REQ = 11;
const int GET_COURSES_SIZE_REQ_MODEL_SPECIFIC = 5;
const int GET_COURSES_SIZE_REQ_MODEL_GENERAL = 3;
const int GET_PERSONAL_PAGE_REQ_SIZE = 5;
const int GET_POST_REQ_SIZE = 7;
const int GET_NOTIFICATION_REQ_SIZE = 3;
const int GET_MY_COURSES_REQ_SIZE = 3;
const int DELETE_MY_COURSES_REQ_SIZE = 5;
const int DELETE_POST_REQ_SIZE = 5;
const int TA_REQ_SIZE = 7;
const int CLOSE_TA_FORM_REQ_SIZE = 5;
const int PROFILE_PHOTO_REQ_SIZE = 5;
const int GET_COURSE_CHANNEL_REQ_SIZE = 5;
const int GET_COURSE_POST_REQ_SIZE = 7;
const int PUT_MY_COURSES_REQ_SIZE = 5;

namespace closed_ta_form_initial_message
{
    const string FIRST_PART = "We have received ";
    const string SECOND_PART = " requests for the teaching assistant position";
}

namespace ta_form_brief_detail_message
{
    const string FIRST_PART = " TA form for ";
    const string SECOND_PART = " course";
}

namespace result_ta_req
{
    const string ACCEPT = "accept";
    const string REJECT = "reject";
}

namespace error_message
{
    const string BAD_REQ = "Bad Request";
    const string EMPTY = "Empty";
    const string NOT_FOUND = "Not Found";
    const string PERMISSION_DENIED = "Permission Denied";
}

namespace request_argument
{
    const string ID = "id";
    const string COURSE_ID = "course_id";
    const string MESSAGE = "message";
    const string TITLE = "title";
    const string IMAGE = "image";
    const string POST_ID = "post_id";
    const string PHOTO = "photo";
    const string PROFESSOR_ID = "professor_id";
    const string FORM_ID = "form_id";
    const string CAPACITY = "capacity";
    const string TIME = "time";
    const string EXAM_DATE = "exam_date";
    const string CLASS_NUMBER = "class_number";
    const string PASSWORD = "password";
}