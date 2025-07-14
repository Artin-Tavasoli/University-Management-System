//#ifndef SERVER_HANDLERS_HPP_INCLUDE
//#define SERVER_HANDLERS_HPP_INCLUDE
#pragma once

#include <map>
#include <string>

#include "../server/server.hpp"
#include "all_error.hpp"
#include "handler.hpp"

class LoginHandler : public RequestHandler
{
public:
    LoginHandler(Handler *_utms_handler);
    Response *callback(Request *) override;

private:
    Handler *utms_handler;
};

class AddCourseHandler : public RequestHandler
{
public:
    AddCourseHandler(Handler *_utms_handler);
    Response *callback(Request *) override;

private:
    Handler *utms_handler;
};

class ShowCoursesPageHandler : public RequestHandler
{
public:
    ShowCoursesPageHandler(Handler *_utms_handler);
    Response *callback(Request *) override;

private:
    Handler *utms_handler;
};
class ShowMyCoursesPageHandler : public RequestHandler
{
public:
    ShowMyCoursesPageHandler(Handler *_utms_handler);
    Response *callback(Request *) override;

private:
    Handler *utms_handler;
};
class RegisterCoursePageHandler : public RequestHandler
{
public:
    RegisterCoursePageHandler(Handler *_utms_handler);
    Response *callback(Request *) override;

private:
    Handler *utms_handler;
};
class DeleteCoursePageHandler : public RequestHandler
{
public:
    DeleteCoursePageHandler(Handler *_utms_handler);
    Response *callback(Request *) override;

private:
    Handler *utms_handler;
};

class HomePageHandler : public RequestHandler
{
public:
    HomePageHandler(Handler *_utms_handler);
    Response *callback(Request *) override;

private:
    Handler *utms_handler;
};

class SearchPageHandler : public RequestHandler
{
public:
    SearchPageHandler(Handler *_utms_handler);
    Response *callback(Request *) override;

private:
    Handler *utms_handler;
};

class AddPostHandler : public RequestHandler
{
public:
    AddPostHandler(Handler *_utms_handler, Server *_server);
    Response *callback(Request *req);

private:
    Handler *utms_handler;
    Server *server;
};

class AddProfileHandler : public RequestHandler
{
public:
    AddProfileHandler(Handler *_utms_handler, Server *_server);
    Response *callback(Request *req);

private:
    Handler *utms_handler;
    Server *server;
};

class DeleteProfileHandler : public RequestHandler
{
public:
    DeleteProfileHandler(Handler *_utms_handler);
    Response *callback(Request *req);

private:
    Handler *utms_handler;
};

class UploadHandler : public RequestHandler
{
public:
    Response *callback(Request *) override;
};


//#endif
