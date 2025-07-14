#include "includes.hpp"
#include "../server/server.hpp"
#include "server_handlers.hpp"
#include "handler.hpp"
void mapServerPaths(Server &server, Handler &handler)
{
    {
        server.setNotFoundErrPage(static_html_path::NOT_FOUND_ERROR_PAGE);
    }
    {
        server.get(url_path::HOME, new ShowPage(static_html_path::HOME));
    }
    {
        server.get(url_path::HOME_LOGO, new ShowImage(static_pics_path::HOME_LOGO));
        server.get(url_path::UNI_BG, new ShowImage(static_pics_path::UNI_BG));
        server.get(url_path::LOGIN_BG, new ShowImage(static_pics_path::LOGIN_BG));
        server.get(url_path::HOMEPAGE_BG, new ShowImage(static_pics_path::HOMEPAGE_BG));
        server.get(url_path::UNLOGGED_PROFILE, new ShowImage(static_pics_path::UNLOGGED_PROFILE));
    }
    {
        server.get(url_path::LOGIN, new ShowPage(static_html_path::LOGIN));
        server.post(url_path::LOGIN, new LoginHandler(&handler));
    }
    {
        server.get(url_path::ADD_COURSE, new ShowPage(static_html_path::ADD_COURSE));
        server.post(url_path::ADD_COURSE, new AddCourseHandler(&handler));
    }
    {
        server.get(url_path::ADD_POST, new ShowPage(static_html_path::ADD_POST));
        server.post(url_path::ADD_POST, new AddPostHandler(&handler, &server));
    }
    {
        server.get(url_path::ADD_PROFILE_PHOTO, new ShowPage(static_html_path::ADD_PROFILE_PHOTO));
        server.post(url_path::ADD_PROFILE_PHOTO, new AddProfileHandler(&handler, &server));
    }
    {
        server.get(url_path::SEARCH_PAGE, new ShowPage(static_html_path::SEARCH_PAGE));
        server.post(url_path::SEARCH_PAGE, new SearchPageHandler(&handler));
    }
    {
        server.get(url_path::REGISTER_COURSE, new ShowPage(static_html_path::REGISTER_COURSE));
        server.post(url_path::REGISTER_COURSE, new RegisterCoursePageHandler(&handler));
    }
    {
        server.get(url_path::DELETE_COURSE, new ShowPage(static_html_path::DELETE_COURSE));
        server.post(url_path::DELETE_COURSE, new DeleteCoursePageHandler(&handler));
    }
    {
        server.get(url_path::DELETE_PROFILE_PHOTO, new DeleteProfileHandler(&handler));
    }
    {
        server.get(url_path::UPLOAD_PAGE, new ShowPage(static_html_path::UPLOAD_PAGE));
        server.post(url_path::UPLOAD_PAGE, new UploadHandler());
    }
    {
        server.get(url_path::HOMEPAGE, new HomePageHandler(&handler));
    }
    {
        server.get(url_path::SHOW_COURSES, new ShowCoursesPageHandler(&handler));
    }
    {
        server.get(url_path::SHOW_MY_COURSES, new ShowMyCoursesPageHandler(&handler));
    }
}
void run_program(int argc, char *argv[])
{
    vector<string> file_paths;
    for (int i = 1; i < argc; i++)
    {
        file_paths.push_back(argv[i]);
    }
    try
    {
        Handler handler(file_paths);
        Server server(SERVER_PORT);
        mapServerPaths(server, handler);
        cout << SERVER_RUNNING_MESSAGE << SERVER_PORT << endl;
        server.run();
    }
    catch (const std::invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
    catch (const Server::Exception &e)
    {
        cerr << e.getMessage() << endl;
    }
}

int main(int argc, char *argv[])
{
    run_program(argc, argv);
    return 0;
}