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
const char COMMAND_ARG_AND_TYPE_DELIMETER = '?';

const string GET_COMMAND = "GET";
const string PUT_COMMAND = "PUT";
const string POST_COMMAND = "POST";
const string DELETE_COMMAND = "DELETE";

const string LOGIN_REQ = "login";
const string LOGOUT_REQ = "logout";
const string COURSES_REQ = "courses";
const string POST_REQ = "post";
const string PERSONAL_PAGE_REQ = "personal_page";
const string CONNECT_REQ = "connect";
const string NOTIFFICATION_REQ = "notification";
const string COURSE_OFFER_REQ = "course_offer";
const string My_COURSES_REQ = "my_courses";

const string DEFAULT_USER_ID = "0";
const string DEFAULT_USER_NAME = "UT_account";
const string DEFAULT_USER_PASSWORD = "UT_account";

const string SUCCESSFULLY_FINISHED_REQ_MESSAGE = "OK";
const string ADDED_LECTURE_NOTIFICATION_MESSAGE = "New Course Offering";
const string ADDED_POST_NOTIFICATION_MESSAGE = "New Post";
const string GET_LECTURE_NOTIFICATION = "Get Course";
const string DELETE_LECTURE_NOTIFICATION = "Delete Course";

const int MAJORS_PATH_NUM = 0;
const int STUDENTS_PATH_NUM = 1;
const int COURSES_PATH_NUM = 2;
const int PROFESSORS_PATH_NUM = 3;

const int LOGIN_SIZE_REQ = 7;
const int LOGOUT_SIZE_REQ = 3;
const int CONNECT_SIZE_REQ = 5;
const int COURSE_OFFER_SIZE_REQ = 15;
const int GET_COURSES_SIZE_REQ_MODEL_SPECIFIC = 5;
const int GET_COURSES_SIZE_REQ_MODEL_GENERAL = 3;
const int GET_PERSONAL_PAGE_REQ_SIZE = 5;
const int GET_POST_REQ_SIZE = 7;
const int GET_NOTIFICATION_REQ_SIZE = 3;
const int GET_MY_COURSES_REQ_SIZE = 3;
const int DELETE_MY_COURSES_REQ_SIZE = 5;
const int DELETE_POST_REQ_SIZE = 5;

