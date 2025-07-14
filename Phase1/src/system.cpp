#include "system.hpp"
enum COMMAND_TYPE
{
    GET,
    POST,
    DELETE,
    PUT,
    NOT_A_TYPE
};

COMMAND_TYPE convert_to_enum(string command)
{
    if (command == GET_COMMAND)
        return GET;
    else if (command == POST_COMMAND)
        return POST;
    else if (command == DELETE_COMMAND)
        return DELETE;
    else if (command == PUT_COMMAND)
        return PUT;
    else
        return NOT_A_TYPE;
}

System::System(Handler *_handler)
{
    utms_handler = _handler;
}

void System::check_size_post_req(const vector<string> splitied_req)
{
    if (splitied_req[1] == LOGIN_REQ && splitied_req.size() != LOGIN_SIZE_REQ)
    {
        throw BadReqExeption();
    }
    else if (splitied_req[1] == LOGOUT_REQ && splitied_req.size() != LOGOUT_SIZE_REQ)
    {
        throw BadReqExeption();
    }
    else if (splitied_req[1] == CONNECT_REQ && splitied_req.size() != CONNECT_SIZE_REQ)
    {
        throw BadReqExeption();
    }
    else if (splitied_req[1] == My_COURSES_REQ && splitied_req.size() != COURSE_OFFER_SIZE_REQ)
    {
        throw BadReqExeption();
    }
}

vector<string> System::put_together_spaced_words(const vector<string> splitied_req)
{
    vector<string> req;
    for (int i = 0; i < splitied_req.size(); i++)
    {
        if (splitied_req[i][0] == '"')
        {
            string text_with_spaces;
            for (int j = i; j < splitied_req.size(); j++)
            {
                i++;
                text_with_spaces += splitied_req[j] + " ";
                if (splitied_req[j][splitied_req[j].size() - 1] == '"')
                {
                    text_with_spaces.erase(text_with_spaces.begin() + text_with_spaces.size() - 1);
                    break;
                }
            }
            req.push_back(text_with_spaces);
            i--;
        }
        else
        {
            req.push_back(splitied_req[i]);
        }
    }
    return req;
}

void System::handle_login()
{
    if (!utms_handler->is_user_logged_in())
        throw PermissionExeption();
}

void System::handle_valid_post(const vector<string> splitied_req)
{
    handle_arg_type_delimeter(splitied_req[2]);
    check_size_post_req(splitied_req);
    handle_login();
}

void System::handle_valid_get(const vector<string> splitied_req)
{
    handle_arg_type_delimeter(splitied_req[2]);
    check_size_get_req(splitied_req);
    handle_login();
}

void System::handle_valid_delete(const vector<string> splitied_req)
{
    handle_arg_type_delimeter(splitied_req[2]);
    check_size_delete_req(splitied_req);
    handle_login();
}

vector<string> System::send_post_command(const vector<string> splitied_req)
{
    vector<string> output;
    vector<string> fixed_req;
    if (splitied_req[1] == LOGIN_REQ)
    {
        handle_arg_type_delimeter(splitied_req[2]);
        check_size_post_req(splitied_req);
        output = utms_handler->login(splitied_req);
    }
    else if (splitied_req[1] == LOGOUT_REQ)
    {
        handle_valid_post(splitied_req);
        output = utms_handler->logout();
    }
    else if (splitied_req[1] == POST_REQ)
    {
        fixed_req = put_together_spaced_words(splitied_req);
        handle_arg_type_delimeter(splitied_req[2]);
        if (fixed_req.size() != 7)
        {
            throw BadReqExeption();
        }
        handle_login();
        output = utms_handler->add_post(fixed_req);
    }
    else if (splitied_req[1] == CONNECT_REQ)
    {
        handle_valid_post(splitied_req);
        output = utms_handler->add_connect(splitied_req);
    }
    else if (splitied_req[1] == COURSE_OFFER_REQ)
    {
        handle_valid_post(splitied_req);
        output = utms_handler->add_course(splitied_req);
    }
    else
    {
        throw NotFoundExeption();
    }
    return output;
}

void System::check_size_get_req(const vector<string> splitied_req)
{
    if (splitied_req[1] == COURSES_REQ && !(splitied_req.size() == GET_COURSES_SIZE_REQ_MODEL_GENERAL || splitied_req.size() == GET_COURSES_SIZE_REQ_MODEL_SPECIFIC))
    {
        throw BadReqExeption();
    }
    else if (splitied_req[1] == PERSONAL_PAGE_REQ && splitied_req.size() != GET_PERSONAL_PAGE_REQ_SIZE)
    {
        throw BadReqExeption();
    }
    else if (splitied_req[1] == POST_REQ && splitied_req.size() != GET_POST_REQ_SIZE)
    {
        throw BadReqExeption();
    }
    else if (splitied_req[1] == NOTIFFICATION_REQ && splitied_req.size() != GET_NOTIFICATION_REQ_SIZE)
    {
        throw BadReqExeption();
    }
    else if (splitied_req[1] == My_COURSES_REQ && splitied_req.size() != GET_MY_COURSES_REQ_SIZE)
    {
        throw BadReqExeption();
    }
}

vector<string> System::send_get_command(const vector<string> splitied_req)
{
    vector<string> output;
    if (splitied_req[1] == COURSES_REQ)
    {
        handle_valid_get(splitied_req);
        output = utms_handler->get_courses(splitied_req);
    }
    else if (splitied_req[1] == PERSONAL_PAGE_REQ)
    {
        handle_valid_get(splitied_req);
        output = utms_handler->get_personal_page(splitied_req);
    }
    else if (splitied_req[1] == POST_REQ)
    {
        handle_valid_get(splitied_req);
        output = utms_handler->get_post(splitied_req);
    }
    else if (splitied_req[1] == NOTIFFICATION_REQ)
    {
        handle_valid_get(splitied_req);
        output = utms_handler->get_notification();
    }
    else if (splitied_req[1] == My_COURSES_REQ)
    {
        handle_valid_get(splitied_req);
        output = utms_handler->get_my_courses();
    }
    else
    {
        throw NotFoundExeption();
    }
    return output;
}

void System::check_size_delete_req(const vector<string> splitied_req)
{
    if (splitied_req[1] == POST_REQ && splitied_req.size() != DELETE_POST_REQ_SIZE)
    {
        throw BadReqExeption();
    }
    else if (splitied_req[1] == My_COURSES_REQ && splitied_req.size() != DELETE_MY_COURSES_REQ_SIZE)
    {
        throw BadReqExeption();
    }
}

vector<string> System::send_delete_command(const vector<string> splitied_req)
{
    vector<string> output;
    if (splitied_req[1] == POST_REQ)
    {
        handle_valid_delete(splitied_req);
        output = utms_handler->delete_post(splitied_req);
    }
    else if (splitied_req[1] == My_COURSES_REQ)
    {
        handle_valid_delete(splitied_req);
        output = utms_handler->delete_course(splitied_req);
    }
    else
    {
        throw NotFoundExeption();
    }
    return output;
}

vector<string> System::send_put_command(const vector<string> splitied_req)
{
    vector<string> output;
    if (splitied_req[1] == My_COURSES_REQ)
    {
        handle_arg_type_delimeter(splitied_req[2]);
        if (splitied_req.size() != 5)
        {
            throw BadReqExeption();
        }
        handle_login();
        output = utms_handler->register_my_course(splitied_req);
    }
    else
    {
        throw NotFoundExeption();
    }
    return output;
}

void System::run()
{
    string request_line;
    while (getline(cin, request_line))
    {
        vector<string> output;
        vector<string> splited_req = split(request_line, BETWEEN_COMMAND_DELIMETER);
        COMMAND_TYPE command_type = convert_to_enum(splited_req[0]);
        switch (command_type)
        {
        case GET:
            try
            {
                output = send_get_command(splited_req);
                break;
            }
            catch (ErrorExeption &ex)
            {
                ex.print_error();
                break;
            }
            break;
        case POST:
            try
            {
                output = send_post_command(splited_req);
                break;
            }
            catch (ErrorExeption &ex)
            {
                ex.print_error();
                break;
            }
        case PUT:
            try
            {
                output = send_put_command(splited_req);
                break;
            }
            catch (ErrorExeption &ex)
            {
                ex.print_error();
                break;
            }
            break;
        case DELETE:
            try
            {
                output = send_delete_command(splited_req);
                break;
            }
            catch (ErrorExeption &ex)
            {
                ex.print_error();
                break;
            }
            break;
        case NOT_A_TYPE:
            ErrorExeption *ex = new BadReqExeption();
            ex->print_error();
            break;
        }
        print_output(output);
    }
}

void System::handle_arg_type_delimeter(string str)
{
    if (str != "?")
        throw BadReqExeption();
}

void System::print_output(vector<string> &output)
{
    for (int i = 0; i < output.size(); i++)
        cout << output[i] << endl;
}
