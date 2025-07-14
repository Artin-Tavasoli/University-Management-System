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
const string ERROR_MESSAGE = "[ERROR_MESSAGE]";
const string SERVER_RUNNING_MESSAGE = "Server running on port: ";

const int SERVER_PORT = 8080;

const char DIFFERENT_TYPE_DELIMETER = ',';
const char SAME_TYPE_DELIMETER = ';';
const char BETWEEN_COMMAND_DELIMETER = ' ';
const string COMMAND_ARG_AND_TYPE_DELIMETER = "?";
const string IMAGE_FORMAT = ".png";

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
    const string USERNAME = "username";
    const string COURSE_ID = "course_id";
    const string MESSAGE = "message";
    const string TITLE = "title";
    const string IMAGE = "image";
    const string IMAGE_PATH = "image_path";
    const string POST_ID = "post_id";
    const string PHOTO = "photo";
    const string PROFILE_PICTURE = "profile_picture";
    const string PROFESSOR_ID = "professor_id";
    const string FORM_ID = "form_id";
    const string CAPACITY = "capacity";
    const string TIME = "time";
    const string EXAM_DATE = "exam_date";
    const string CLASS_NUMBER = "class_number";
    const string PASSWORD = "password";
}
namespace static_html_path
{
    const string ERROR_PAGE = "static/error_page.html";
    const string NOT_FOUND_ERROR_PAGE = "static/404.html";
    const string HOME = "static/home.html";
    const string LOGIN = "static/logincss.html";
    const string ADD_COURSE = "static/add_course.html";
    const string ADD_POST = "static/add_post.html";
    const string ADD_PROFILE_PHOTO = "static/add_profile_photo.html";
    const string SEARCH_PAGE = "static/search_page.html";
    const string REGISTER_COURSE = "static/register_course.html";
    const string DELETE_COURSE = "static/delete_course.html";
    const string UPLOAD_PAGE = "static/uploads_form.html";
}

namespace static_pics_path
{
    const string HOME_LOGO = "static/home.png";
    const string UNI_BG = "static/uni_background.jpg";
    const string LOGIN_BG = "static/login_bg.jpg";
    const string HOMEPAGE_BG = "static/homepage_bg.jpg";
    const string UNLOGGED_PROFILE = "static/unlogged_profile_pic.png";

}

namespace url_path
{
    const string HOME = "/";
    const string HOME_LOGO = "/home.png";
    const string UNI_BG = "/uni_background.jpg";
    const string LOGIN_BG = "/login_bg.jpg";
    const string HOMEPAGE_BG = "/homepage_bg.jpg";
    const string UNLOGGED_PROFILE = "/unlogged_profile_pic.png";
    const string LOGIN = "/login";
    const string ADD_COURSE = "/add_course";
    const string ADD_POST = "/add_post";
    const string ADD_PROFILE_PHOTO = "/add_profile_photo";
    const string SEARCH_PAGE = "/search_page";
    const string REGISTER_COURSE = "/register_course";
    const string DELETE_COURSE = "/delete_course";
    const string UPLOAD_PAGE = "/up";
    const string DELETE_PROFILE_PHOTO = "/delete_profile_photo";
    const string HOMEPAGE = "/homepage_handler";
    const string SHOW_COURSES = "/show_courses";
    const string SHOW_MY_COURSES = "/show_my_courses";
}

const string HOMEPAGE = R"(<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Personal Page</title>
    <style>
        html,
        body {
            height: 100%;
            margin: 0;
            padding: 0;
            background-image: url('homepage_bg.jpg');
            background-size: cover;
            background-position: center;
            background-repeat: no-repeat;
            background-attachment: fixed;
            background-color: violet;
            color: white;
            text-align: center;
        }

        body {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        .header {
            font-size: 60px;
            color: blue;
            margin-top: 20px;
        }

        .box {
            background-color: rgba(255, 255, 255, 0.9);
            color: black;
            padding: 20px;
            border-radius: 10px;
            margin: 20px 0;
            text-align: center;
            width: 300px;
        }

        .box a {
            color: blueviolet;
            text-decoration: none;
            font-size: 24px;
        }

        .profile-photo {
            width: 150px;
            height: 150px;
            border-radius: 50%;
            object-fit: cover;
            margin-bottom: 20px;
        }

        .post-pic {
            width: 300px;
            height: 200px;
            object-fit: cover;
            border-radius: 10px;
        }

        .user-details {
            text-align: left;
        }

        /* Sidebar Menu */
        .sidebar {
            height: 100%;
            width: 0;
            position: fixed;
            top: 0;
            left: 0;
            background-color: rgba(0, 0, 0, 0.8);
            overflow-x: hidden;
            transition: 0.5s;
            padding-top: 60px;
            text-align: left;
        }

        .sidebar a {
            padding: 8px 8px 8px 32px;
            text-decoration: none;
            font-size: 25px;
            color: white;
            display: block;
            transition: 0.3s;
        }

        .sidebar a:hover {
            color: #f1f1f1;
        }

        .sidebar .closebtn {
            position: absolute;
            top: 0;
            right: 25px;
            font-size: 36px;
            margin-left: 50px;
        }

        .openbtn {
            font-size: 20px;
            cursor: pointer;
            background-color: rgba(0, 0, 0, 0.7);
            color: white;
            padding: 10px 15px;
            border: none;
            margin: 10px;
            position: fixed;
            top: 20px;
            left: 20px;
        }
    </style>
</head>

<body>
    <h1 class="header">PERSONAL PAGE</h1>

    <button class="openbtn" onclick="openNav() ">☰ Menu</button>
    <script>
        function openNav() {
            document.getElementById("mySidebar").style.width = "250px";
        }

        function closeNav() {
            document.getElementById("mySidebar").style.width = "0";
        }
    </script>
)";

const string ANOTHER_USER_HOMEPAGE = R"(<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Personal Page</title>
    <style>
        html,
        body {
            height: 100%;
            margin: 0;
            padding: 0;
            background-image: url('homepage_bg.jpg');
            background-size: cover;
            background-position: center;
            background-repeat: no-repeat;
            background-attachment: fixed;
            background-color: violet;
            color: white;
            text-align: center;
        }

        body {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        .header {
            font-size: 60px;
            color: blue;
            margin-top: 20px;
        }

        .box {
            background-color: rgba(255, 255, 255, 0.9);
            color: black;
            padding: 20px;
            border-radius: 10px;
            margin: 20px 0;
            text-align: center;
            width: 300px;
        }

        .box a {
            color: blueviolet;
            text-decoration: none;
            font-size: 24px;
        }

        .profile-photo {
            width: 150px;
            height: 150px;
            border-radius: 50%;
            object-fit: cover;
            margin-bottom: 20px;
        }
        .post-pic {
             width: 300px;
            height: 200px;
            object-fit: cover;
            border-radius: 10px;
        }

        .user-details {
            text-align: left;
        }
    </style>
</head>

<body>
    <h1 class="header">PERSONAL PAGE</h1>
)";

const string SHOW_COURSES = R"(<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>COURSES</title>
    <style>
        html,
        body {
            height: 100%;
            margin: 0;
            padding: 0;
            background-image: url('homepage_bg.jpg');
            background-size: cover;
            background-position: center;
            background-repeat: no-repeat;
            background-attachment: fixed;
            background-color: violet;
            color: white;
            text-align: center;
        }

        body {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        .header {
            font-size: 60px;
            color: blue;
            margin-top: 20px;
        }

        .box {
            background-color: rgba(255, 255, 255, 0.9);
            color: black;
            padding: 20px;
            border-radius: 10px;
            margin: 20px 0;
            text-align: center;
            width: 300px;
        }

        .box a {
            color: blueviolet;
            text-decoration: none;
            font-size: 24px;
        }

        .profile-photo {
            width: 150px;
            height: 150px;
            border-radius: 50%;
            object-fit: cover;
            margin-bottom: 20px;
        }
        .post-pic {
            width: 300px;
            height: 200px;
            object-fit: cover;
            border-radius: 10px;
        }
        
        .user-details {
            text-align: left;
        }
    </style>
</head>

<body>
    <h1 class="header">COURSES</h1>
)";

const string SHOW_MY_COURSES = R"(<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MY_COURSES</title>
    <style>
        html,
        body {
            height: 100%;
            margin: 0;
            padding: 0;
            background-image: url('homepage_bg.jpg');
            background-size: cover;
            background-position: center;
            background-repeat: no-repeat;
            background-attachment: fixed;
            background-color: violet;
            color: white;
            text-align: center;
        }

        body {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        .header {
            font-size: 60px;
            color: blue;
            margin-top: 20px;
        }

        .box {
            background-color: rgba(255, 255, 255, 0.9);
            color: black;
            padding: 20px;
            border-radius: 10px;
            margin: 20px 0;
            text-align: center;
            width: 300px;
        }

        .box a {
            color: blueviolet;
            text-decoration: none;
            font-size: 24px;
        }

        .profile-photo {
            width: 150px;
            height: 150px;
            border-radius: 50%;
            object-fit: cover;
            margin-bottom: 20px;
        }
        .post-pic {
            width: 300px;
            height: 200px;
            object-fit: cover;
            border-radius: 10px;
        }

        .user-details {
            text-align: left;
        }
    </style>
</head>

<body>
    <h1 class="header">MY_COURSES</h1>
)";
