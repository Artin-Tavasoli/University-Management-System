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

void System::check_size_post_req(const vector<string> splitted_req)
{
    if (splitted_req[1] == LOGIN_REQ && splitted_req.size() != LOGIN_SIZE_REQ)
        throw BadReqExeption();
    else if (splitted_req[1] == LOGOUT_REQ && splitted_req.size() != LOGOUT_SIZE_REQ)
        throw BadReqExeption();
    else if (splitted_req[1] == CONNECT_REQ && splitted_req.size() != CONNECT_SIZE_REQ)
        throw BadReqExeption();
    else if (splitted_req[1] == My_COURSES_REQ && splitted_req.size() != COURSE_OFFER_SIZE_REQ)
        throw BadReqExeption();
    else if (splitted_req[1] == TA_REQ && splitted_req.size() != TA_REQ_SIZE)
        throw BadReqExeption();
    else if (splitted_req[1] == CLOSE_TA_FORM_REQ && splitted_req.size() != CLOSE_TA_FORM_REQ_SIZE)
        throw BadReqExeption();
    else if (splitted_req[1] == PROFILE_PHOTO_REQ && splitted_req.size() != PROFILE_PHOTO_REQ_SIZE)
        throw BadReqExeption();
    else if (splitted_req[1] == NORMAL_POST_REQ)
    {
        if (!(splitted_req.size() == NORMAL_POST_WITHOUT_IMAGE_SIZE_REQ || splitted_req.size() == NORMAL_POST_WITH_IMAGE_SIZE_REQ))
            throw BadReqExeption();
    }
    else if (splitted_req[1] == TA_FORM_POST_REQ && splitted_req.size() != TA_FORM_POST_SIZE_REQ)
        throw BadReqExeption();
    else if (splitted_req[1] == COURSE_POST_REQ)
    {
        if (!(splitted_req.size() == COURSE_POST_WITHOUT_IMAGE_SIZE_REQ || splitted_req.size() == COURSE_POST_WITH_IMAGE_SIZE_REQ))
            throw BadReqExeption();
    }
}

vector<string> System::put_together_spaced_words(const vector<string> splitted_req)
{
    vector<string> req;
    for (int i = 0; i < splitted_req.size(); i++)
    {
        if (splitted_req[i][0] == '"')
        {
            string text_with_spaces;
            for (int j = i; j < splitted_req.size(); j++)
            {
                i++;
                text_with_spaces += splitted_req[j] + " ";
                if (splitted_req[j][splitted_req[j].size() - 1] == '"')
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
            req.push_back(splitted_req[i]);
        }
    }
    return req;
}

void System::handle_login()
{
    if (!utms_handler->is_user_logged_in())
        throw PermissionExeption();
}

void System::handle_valid_post(const vector<string> splitted_req)
{
    handle_arg_type_delimeter(splitted_req);
    check_size_post_req(splitted_req);
    handle_login();
}

void System::handle_valid_get(const vector<string> splitted_req)
{
    handle_arg_type_delimeter(splitted_req);
    check_size_get_req(splitted_req);
    handle_login();
}

void System::handle_valid_delete(const vector<string> splitted_req)
{
    handle_arg_type_delimeter(splitted_req);
    check_size_delete_req(splitted_req);
    handle_login();
}

vector<string> System::get_login_req_data(const vector<string> splitted_req)
{
    int arg_counter = 0;
    string password, id;
    for (int i = 0; i < splitted_req.size() - 1; i++)
    {
        if (splitted_req[i] == request_argument::ID)
        {
            arg_counter++;
            id = splitted_req[i + 1];
        }
        if (splitted_req[i] == request_argument::PASSWORD)
        {
            password = splitted_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 2)
        throw BadReqExeption();
    return {id, password};
}

vector<string> System::get_add_course_req_data(const vector<string> splitted_req)
{
    string course_id, pid, class_number, time, exam_date, capacity;
    int arg_counter = 0;
    for (int i = 0; i < splitted_req.size() - 1; i++)
    {
        if (splitted_req[i] == request_argument::COURSE_ID)
        {
            course_id = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::PROFESSOR_ID)
        {
            pid = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::CAPACITY)
        {
            capacity = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::TIME)
        {
            time = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::EXAM_DATE)
        {
            exam_date = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::CLASS_NUMBER)
        {
            class_number = splitted_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 6)
        throw BadReqExeption();
    return {course_id, pid, class_number, time, exam_date, capacity};
}

vector<string> System::get_add_normal_post_req_data(const vector<string> splitted_req)
{
    int arg_counter = 0, image_arg_counter = 0;
    string title, message, image_path = "";
    for (int i = 0; i < splitted_req.size() - 1; i++)
    {
        if (splitted_req[i] == request_argument::TITLE)
        {
            title = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::MESSAGE)
        {
            message = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::IMAGE)
        {
            image_path = splitted_req[i + 1];
            image_arg_counter++;
        }
    }
    if (arg_counter != 2)
    {
        throw BadReqExeption();
    }
    if (image_arg_counter > 1)
        throw BadReqExeption();
    return {title, message, image_path};
}

vector<string> System::get_send_ta_req_data(const vector<string> splitted_req)
{
    int arg_counter = 0;
    string pid, form_id;
    for (int i = 0; i < splitted_req.size() - 1; i++)
    {
        if (splitted_req[i] == request_argument::PROFESSOR_ID)
        {
            pid = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::FORM_ID)
        {
            form_id = splitted_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 2)
        throw BadReqExeption();
    return {pid, form_id};
}

vector<string> System::get_get_course_post_data(const vector<string> splitted_req)
{
    int arg_counter = 0;
    string lecture_id, post_id;
    for (int i = 0; i < splitted_req.size() - 1; i++)
    {
        if (splitted_req[i] == request_argument::ID)
        {
            lecture_id = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::POST_ID)
        {
            post_id = splitted_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 2)
        throw BadReqExeption();
    return {lecture_id, post_id};
}

vector<string> System::send_post_command(const vector<string> splitted_req)
{
    vector<string> output;
    vector<string> fixed_req;
    if (splitted_req[1] == LOGIN_REQ)
    {
        handle_arg_type_delimeter(splitted_req);
        check_size_post_req(splitted_req);
        vector<string> input = get_login_req_data(splitted_req);
        output = utms_handler->login(input[0], input[1]);
    }
    else if (splitted_req[1] == LOGOUT_REQ)
    {
        handle_valid_post(splitted_req);
        output = utms_handler->logout();
    }
    else if (splitted_req[1] == NORMAL_POST_REQ)
    {
        fixed_req = put_together_spaced_words(splitted_req);
        handle_valid_post(fixed_req);
        vector<string> input = get_add_normal_post_req_data(fixed_req);
        output = utms_handler->add_normal_post(input[0], input[1], input[2]);
    }
    else if (splitted_req[1] == TA_FORM_POST_REQ)
    {
        fixed_req = put_together_spaced_words(splitted_req);
        handle_valid_post(fixed_req);
        vector<string> input = get_add_ta_form_post_data(fixed_req);
        output = utms_handler->add_ta_form_post(input[0], input[1]);
    }
    else if (splitted_req[1] == COURSE_POST_REQ)
    {
        fixed_req = put_together_spaced_words(splitted_req);
        handle_valid_post(fixed_req);
        vector<string> input = get_course_post_req_data(fixed_req);
        output = utms_handler->add_course_post(input[0], input[1], input[2], input[3]);
    }
    else if (splitted_req[1] == CONNECT_REQ)
    {
        handle_valid_post(splitted_req);
        if (splitted_req[3] != request_argument::ID)
            throw BadReqExeption();
        output = utms_handler->add_connect(splitted_req[4]);
    }
    else if (splitted_req[1] == COURSE_OFFER_REQ)
    {
        handle_valid_post(splitted_req);
        vector<string> input = get_add_course_req_data(splitted_req);
        output = utms_handler->add_course(input[0], input[1], input[2], input[3], input[4], input[5]);
    }
    else if (splitted_req[1] == TA_REQ)
    {
        handle_valid_post(splitted_req);
        vector<string> input = get_send_ta_req_data(splitted_req);
        output = utms_handler->send_ta_req(input[0], input[1]);
    }
    else if (splitted_req[1] == CLOSE_TA_FORM_REQ)
    {
        handle_valid_post(splitted_req);
        handle_close_ta_form_req(splitted_req);
    }
    else if (splitted_req[1] == PROFILE_PHOTO_REQ)
    {
        handle_valid_post(splitted_req);
        if (splitted_req[3] != request_argument::PHOTO)
            throw BadReqExeption();
        output = utms_handler->add_profile_photo(splitted_req[4]);
    }
    else
        throw NotFoundExeption();
    return output;
}

void System::handle_close_ta_form_req(const vector<string> splitted_req)
{
    if (splitted_req[3] != request_argument::ID)
        throw BadReqExeption();
    vector<Ta_applicant_info *> ta_applicants_info = utms_handler->close_ta_form_req(splitted_req[4]);
    cout << closed_ta_form_initial_message::FIRST_PART << ta_applicants_info.size() << closed_ta_form_initial_message::SECOND_PART << endl;
    get_ta_applicants_results(ta_applicants_info);
    utms_handler->handle_ta_results(ta_applicants_info, splitted_req[4]);
    utms_handler->delete_post(splitted_req[4]);
    for (int i = 0; i < ta_applicants_info.size(); i++)
        delete ta_applicants_info[i];
    ta_applicants_info.clear();
}

void System::check_size_get_req(const vector<string> splitted_req)
{
    if (splitted_req[1] == COURSES_REQ && !(splitted_req.size() == GET_COURSES_SIZE_REQ_MODEL_GENERAL || splitted_req.size() == GET_COURSES_SIZE_REQ_MODEL_SPECIFIC))
        throw BadReqExeption();
    else if (splitted_req[1] == PERSONAL_PAGE_REQ && splitted_req.size() != GET_PERSONAL_PAGE_REQ_SIZE)
        throw BadReqExeption();
    else if (splitted_req[1] == NORMAL_POST_REQ && splitted_req.size() != GET_POST_REQ_SIZE)
        throw BadReqExeption();
    else if (splitted_req[1] == NOTIFFICATION_REQ && splitted_req.size() != GET_NOTIFICATION_REQ_SIZE)
        throw BadReqExeption();
    else if (splitted_req[1] == My_COURSES_REQ && splitted_req.size() != GET_MY_COURSES_REQ_SIZE)
        throw BadReqExeption();
    else if (splitted_req[1] == GET_COURSE_CHANNEL_REQ && splitted_req.size() != GET_COURSE_CHANNEL_REQ_SIZE)
        throw BadReqExeption();
    else if (splitted_req[1] == GET_COURSE_POST_REQ && splitted_req.size() != GET_COURSE_POST_REQ_SIZE)
        throw BadReqExeption();
}

void System::handle_valid_get_course(const vector<string> splitted_req)
{
    if (splitted_req.size() == 5)
        if (splitted_req[3] != request_argument::ID)
            throw BadReqExeption();
}

vector<string> System::get_get_post_req_data(const vector<string> splitted_req)
{
    int arg_counter = 0;
    string id, post_id;
    for (int i = 0; i < splitted_req.size() - 1; i++)
    {
        if (splitted_req[i] == request_argument::ID)
        {
            id = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::POST_ID)
        {
            post_id = splitted_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 2)
        throw BadReqExeption();
    return {id, post_id};
}

vector<string> System::get_course_post_req_data(const vector<string> splitted_req)
{
    int arg_counter = 0, image_arg_counter = 0;
    string id, title, message, image_path = "";
    for (int i = 0; i < splitted_req.size() - 1; i++)
    {
        if (splitted_req[i] == request_argument::TITLE)
        {
            title = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::ID)
        {
            id = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::MESSAGE)
        {
            message = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::IMAGE)
        {
            image_path = splitted_req[i + 1];
            image_arg_counter++;
        }
    }
    if (arg_counter != 3)
    {
        throw BadReqExeption();
    }
    if (image_arg_counter > 1)
        throw BadReqExeption();
    return {id, title, message, image_path};
}

vector<string> System::get_add_ta_form_post_data(const vector<string> splitted_req)
{
    int arg_counter = 0;
    string lecture_id, message;
    for (int i = 0; i < splitted_req.size() - 1; i++)
    {
        if (splitted_req[i] == request_argument::COURSE_ID)
        {
            lecture_id = splitted_req[i + 1];
            arg_counter++;
        }
        else if (splitted_req[i] == request_argument::MESSAGE)
        {
            message = splitted_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 2)
    {
        throw BadReqExeption();
    }
    return {lecture_id, message};
}

vector<string> System::send_get_command(const vector<string> splitted_req)
{
    vector<string> output;
    if (splitted_req[1] == COURSES_REQ)
    {
        handle_valid_get(splitted_req);
        handle_valid_get_course(splitted_req);
        output = utms_handler->get_courses(splitted_req);
    }
    else if (splitted_req[1] == PERSONAL_PAGE_REQ)
    {
        handle_valid_get(splitted_req);
        if (splitted_req[3] != request_argument::ID)
            throw BadReqExeption();
        output = utms_handler->get_personal_page(splitted_req[4]);
    }
    else if (splitted_req[1] == NORMAL_POST_REQ)
    {
        handle_valid_get(splitted_req);
        vector<string> input = get_get_post_req_data(splitted_req);
        output = utms_handler->get_post(input[0], input[1]);
    }
    else if (splitted_req[1] == NOTIFFICATION_REQ)
    {
        handle_valid_get(splitted_req);
        output = utms_handler->get_notification();
    }
    else if (splitted_req[1] == My_COURSES_REQ)
    {
        handle_valid_get(splitted_req);
        output = utms_handler->get_my_courses();
    }
    else if (splitted_req[1] == GET_COURSE_CHANNEL_REQ)
    {
        handle_valid_get(splitted_req);
        if (splitted_req[3] != "id")
            throw BadReqExeption();
        output = utms_handler->get_course_channel(splitted_req[4]);
    }
    else if (splitted_req[1] == GET_COURSE_POST_REQ)
    {
        handle_valid_get(splitted_req);
        vector<string> input = get_get_course_post_data(splitted_req);
        output = utms_handler->get_course_post(input[0], input[1]);
    }

    else
        throw NotFoundExeption();
    return output;
}

void System::check_size_delete_req(const vector<string> splitted_req)
{
    if (splitted_req[1] == NORMAL_POST_REQ && splitted_req.size() != DELETE_POST_REQ_SIZE)
    {
        throw BadReqExeption();
    }
    else if (splitted_req[1] == My_COURSES_REQ && splitted_req.size() != DELETE_MY_COURSES_REQ_SIZE)
    {
        throw BadReqExeption();
    }
}

vector<string> System::send_delete_command(const vector<string> splitted_req)
{
    vector<string> output;
    if (splitted_req[1] == NORMAL_POST_REQ)
    {
        handle_valid_delete(splitted_req);
        if (splitted_req[3] != request_argument::ID)
            throw BadReqExeption();
        output = utms_handler->delete_post(splitted_req[4]);
    }
    else if (splitted_req[1] == My_COURSES_REQ)
    {
        handle_valid_delete(splitted_req);
        if (splitted_req[3] != request_argument::ID)
            throw BadReqExeption();
        output = utms_handler->delete_course(splitted_req[4]);
    }
    else
    {
        throw NotFoundExeption();
    }
    return output;
}

vector<string> System::send_put_command(const vector<string> splitted_req)
{
    vector<string> output;
    if (splitted_req[1] == My_COURSES_REQ)
    {
        handle_arg_type_delimeter(splitted_req);
        if (splitted_req.size() != PUT_MY_COURSES_REQ_SIZE || splitted_req[3] != request_argument::ID)
        {
            throw BadReqExeption();
        }
        handle_login();
        output = utms_handler->register_my_course(splitted_req[4]);
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
        if (splited_req.empty())
            continue;
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

void System::handle_arg_type_delimeter(const vector<string> splitted_req)
{
    bool found_delimeter = false;
    for (auto req : splitted_req)
        if (req == COMMAND_ARG_AND_TYPE_DELIMETER)
            found_delimeter = true;
    if (!found_delimeter)
        throw BadReqExeption();
}

void System::print_output(vector<string> &output)
{
    for (int i = 0; i < output.size(); i++)
        cout << output[i] << endl;
}

void System::get_ta_applicants_results(vector<Ta_applicant_info *> &ta_applicants_info)
{
    for (auto applicant : ta_applicants_info)
    {
        string req_result;
        do
        {
            cout << applicant->student_id + " " + applicant->student_name + " " + to_string(applicant->semester) + ": ";
            getline(cin, req_result);
        } while (!(req_result == result_ta_req::ACCEPT || req_result == result_ta_req::REJECT));
        applicant->result = req_result;
    }
}