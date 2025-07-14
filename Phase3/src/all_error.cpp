#include "all_error.hpp"
string ErrorExeption::readHtmlFile(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        return "<h1>File not found</h1>";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
Response *ErrorExeption::generate_error_response()
{
    string htmlContent = readHtmlFile(static_html_path::ERROR_PAGE);
    size_t pos = htmlContent.find(ERROR_MESSAGE);
    if (pos != string::npos)
    {
        htmlContent.replace(pos, string(ERROR_MESSAGE).length(), message);
    }
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    res->setBody(htmlContent);
    return res;
}