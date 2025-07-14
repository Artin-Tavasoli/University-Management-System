#include "server_handlers.hpp"

#include <cstdlib>
#include <iostream>

LoginHandler::LoginHandler(Handler *_utms_handler)
{
    utms_handler = _utms_handler;
}

AddCourseHandler::AddCourseHandler(Handler *_utms_handler)
{
    utms_handler = _utms_handler;
}

AddPostHandler::AddPostHandler(Handler *_utms_handler, Server *_server)
{
    utms_handler = _utms_handler;
    server = _server;
}

AddProfileHandler::AddProfileHandler(Handler *_utms_handler, Server *_server)
{
    utms_handler = _utms_handler;
    server = _server;
}

HomePageHandler::HomePageHandler(Handler *_utms_handler)
{
    utms_handler = _utms_handler;
}

DeleteProfileHandler::DeleteProfileHandler(Handler *_utms_handler)
{
    utms_handler = _utms_handler;
}

SearchPageHandler::SearchPageHandler(Handler *_utms_handler)
{
    utms_handler = _utms_handler;
}

ShowCoursesPageHandler::ShowCoursesPageHandler(Handler *_utms_handler)
{
    utms_handler = _utms_handler;
}

ShowMyCoursesPageHandler::ShowMyCoursesPageHandler(Handler *_utms_handler)
{
    utms_handler = _utms_handler;
}

RegisterCoursePageHandler::RegisterCoursePageHandler(Handler *_utms_handler)
{
    utms_handler = _utms_handler;
}

DeleteCoursePageHandler::DeleteCoursePageHandler(Handler *_utms_handler)
{
    utms_handler = _utms_handler;
}

Response *LoginHandler::callback(Request *req)
{
    try
    {
        string username = req->getBodyParam(request_argument::USERNAME);
        string password = req->getBodyParam(request_argument::PASSWORD);
        utms_handler->set_current_user("");
        utms_handler->login(username, password);
        Response *res = new Response;
        res = Response::redirect(url_path::HOMEPAGE);
        utms_handler->set_current_user(username);
        res->setSessionId(username);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *SearchPageHandler::callback(Request *req)
{
    try
    {
        string body = "";
        string username = req->getSessionId();
        string id_to_see_page = req->getBodyParam(request_argument::ID);
        utms_handler->set_current_user(id_to_see_page);
        Response *res = new Response;
        body += ANOTHER_USER_HOMEPAGE;
        body += utms_handler->get_detail_in_html(id_to_see_page);
        body += R"(</body></html>)";
        res->setHeader("Content-Type", "text/html");
        res->setBody(body);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *AddCourseHandler::callback(Request *req)
{

    try
    {
        string course_id = req->getBodyParam(request_argument::COURSE_ID);
        string pid = req->getBodyParam(request_argument::PROFESSOR_ID);
        string class_number = req->getBodyParam(request_argument::CLASS_NUMBER);
        string time = req->getBodyParam(request_argument::TIME);
        string exam_date = req->getBodyParam(request_argument::EXAM_DATE);
        string capacity = req->getBodyParam(request_argument::CAPACITY);
        string username = req->getSessionId();
        if (username != DEFAULT_USER_ID)
            throw PermissionExeption();
        utms_handler->set_current_user(username);
        utms_handler->add_course(course_id, pid, class_number, time, exam_date, capacity);
        Response *res = Response::redirect(url_path::HOMEPAGE);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *RegisterCoursePageHandler::callback(Request *req)
{
    try
    {
        string course_id = req->getBodyParam(request_argument::COURSE_ID);
        string username = req->getSessionId();
        utms_handler->set_current_user(username);
        utms_handler->register_my_course(course_id);
        Response *res = Response::redirect(url_path::HOMEPAGE);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *DeleteCoursePageHandler::callback(Request *req)
{
    try
    {
        string course_id = req->getBodyParam(request_argument::COURSE_ID);
        string username = req->getSessionId();
        utms_handler->set_current_user(username);
        utms_handler->delete_course(course_id);
        Response *res = Response::redirect(url_path::HOMEPAGE);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *HomePageHandler::callback(Request *req)
{
    try
    {
        string username = req->getSessionId();
        utms_handler->set_current_user(username);
        Response *res = new Response;
        string body = "";
        body += HOMEPAGE;
        body += R"(
        <div id="mySidebar" class="sidebar">
        <a href="javascript:void(0) " class="closebtn" onclick="closeNav() ">×</a>
        <a href="/">LOGOUT</a>
        <a href="/add_post">ADD POST</a>
        <a href="/add_profile_photo">ADD PROFILE PHOTO</a>
        <a href="/delete_profile_photo">DELETE PROFILE PHOTO</a>
        <a href="/search_page">SEARCH PAGE</a>
        <a href="/show_courses">SHOW COURSES</a>)";
        if (username == DEFAULT_USER_ID)
            body += R"(<a href="/add_course">ADD COURSE</a>)";
        if (utms_handler->is_current_user_a_student())
        {
            body += R"(
                    <a href="/register_course">REGISTER COURSE</a>
                    <a href="/delete_course">DELETE COURSE</a>
                    <a href="/show_my_courses">SHOW MY COURSE</a>)";
        }
        body += R"(</div>)";
        body += utms_handler->get_detail_in_html(username);
        body += R"(</body></html>)";
        res->setHeader("Content-Type", "text/html");
        res->setBody(body);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *ShowCoursesPageHandler::callback(Request *req)
{
    try
    {
        string username = req->getSessionId();
        utms_handler->set_current_user(username);
        Response *res = new Response;
        string body = "";
        body += SHOW_COURSES;
        body += utms_handler->get_courses_in_html();
        body += R"(</body></html>)";
        res->setHeader("Content-Type", "text/html");
        res->setBody(body);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *ShowMyCoursesPageHandler::callback(Request *req)
{
    try
    {
        string username = req->getSessionId();
        utms_handler->set_current_user(username);
        Response *res = new Response;
        string body = "";
        body += SHOW_MY_COURSES;
        body += utms_handler->get_my_courses_in_html();
        body += R"(</body></html>)";
        res->setHeader("Content-Type", "text/html");
        res->setBody(body);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *AddPostHandler::callback(Request *req)
{
    try
    {
        string title = req->getBodyParam(request_argument::TITLE);
        string message = req->getBodyParam(request_argument::MESSAGE);
        string image_name = req->getBodyParam(request_argument::IMAGE_PATH);
        string username = req->getSessionId();
        utms_handler->set_current_user(username);
        if (image_name != "")
        {
            string pid = utms_handler->get_current_user_post_id_gen();
            string correct = to_string(stoi(pid) + 1);
            string image_path = "/post_pics/" + utms_handler->get_current_user_id() + correct;
            utils::writeToFile(image_name, "uploaded_files/post_pics/" + utms_handler->get_current_user_id() + correct);
            server->get(image_path, new ShowImage("uploaded_files/post_pics/" + utms_handler->get_current_user_id() + correct));
            utms_handler->add_normal_post(title, message, image_path);
        }
        else
        {
            utms_handler->add_normal_post(title, message, "");
        }

        Response *res = Response::redirect(url_path::HOMEPAGE);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *UploadHandler::callback(Request *req)
{
    std::string name = req->getBodyParam("file_name");
    std::string file = req->getBodyParam("file");
    utils::writeToFile(file, name);
    Response *res = Response::redirect("/");
    return res;
}

Response *AddProfileHandler::callback(Request *req)
{

    try
    {
        string username = req->getSessionId();
        utms_handler->set_current_user(username);
        string image = req->getBodyParam(request_argument::PROFILE_PICTURE);
        string image_path = "/profile_pics/" + utms_handler->get_current_user_id();
        utils::writeToFile(image, "uploaded_files/profile_pics/" + utms_handler->get_current_user_id());
        server->get(image_path, new ShowImage("uploaded_files/profile_pics/" + utms_handler->get_current_user_id()));
        utms_handler->set_profile_picture(image_path);
        Response *res = Response::redirect(url_path::HOMEPAGE);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}

Response *DeleteProfileHandler::callback(Request *req)
{

    try
    {
        string username = req->getSessionId();
        utms_handler->set_current_user(username);
        utms_handler->set_profile_picture(url_path::UNLOGGED_PROFILE);
        Response *res = Response::redirect(url_path::HOMEPAGE);
        return res;
    }
    catch (ErrorExeption &ex)
    {
        return ex.generate_error_response();
    }
}
