#include "handler.hpp"

Handler::Handler(const vector<string> &_file_paths)
{
    file_paths = _file_paths;
    set_majors();
    set_students();
    set_courses();
    set_professors();
    set_default_user();
}

void Handler::set_majors()
{
    vector<string> majors_lines = read_from_file_line_by_line(file_paths[MAJORS_PATH_NUM]);
    for (auto line : majors_lines)
    {
        vector<string> major_data = split(line, DIFFERENT_TYPE_DELIMETER);
        Major *the_major = new Major();
        the_major->id = stoi(major_data[0]);
        the_major->name = major_data[1];
        majors.push_back(the_major);
    }
}

void Handler::set_students()
{
    vector<string> students_lines = read_from_file_line_by_line(file_paths[STUDENTS_PATH_NUM]);

    for (auto line : students_lines)
    {
        vector<string> student_data = split(line, DIFFERENT_TYPE_DELIMETER);
        string major_name;
        for (auto major : majors)
        {
            if (major->id == stoi(student_data[2]))
                major_name = major->name;
        }
        Student *the_student = new Student(student_data[0], student_data[1], stoi(student_data[2]), stoi(student_data[3]), student_data[4], major_name);
        students.push_back(the_student);
        users.push_back(the_student);
    }
}

void Handler::set_professors()
{
    vector<string> professors_lines = read_from_file_line_by_line(file_paths[PROFESSORS_PATH_NUM]);
    for (auto line : professors_lines)
    {
        vector<string> professors_data = split(line, DIFFERENT_TYPE_DELIMETER);
        string major_name;
        for (auto major : majors)
        {
            if (major->id == stoi(professors_data[2]))
                major_name = major->name;
        }
        Professor *the_professor = new Professor(professors_data[0], professors_data[1], stoi(professors_data[2]), professors_data[3], professors_data[4], major_name);
        professors.push_back(the_professor);
        users.push_back(the_professor);
    }
}

void Handler::set_courses()
{
    vector<string> courses_lines = read_from_file_line_by_line(file_paths[COURSES_PATH_NUM]);
    for (auto line : courses_lines)
    {
        vector<string> course_data = split(line, DIFFERENT_TYPE_DELIMETER);
        vector<string> majors_id_in_string = split(course_data[4], SAME_TYPE_DELIMETER);
        vector<int> majors_id;
        for (auto id : majors_id_in_string)
            majors_id.push_back(stoi(id));
        Course *the_course = new Course(stoi(course_data[0]), course_data[1], stoi(course_data[2]), stoi(course_data[3]), majors_id);
        courses.push_back(the_course);
    }
}

void Handler::set_default_user()
{
    default_user = new Default_user(DEFAULT_USER_ID, DEFAULT_USER_PASSWORD);
    for (auto user : users)
    {
        if (user->get_id() != DEFAULT_USER_ID)
            default_user->add_connect(user);
    }
    users.push_back(default_user);
}

void Handler::set_current_user(string _id)
{
    if (_id == "")
        current_user = NULL;
    else if (find_student(_id) != NULL)
        current_user = find_student(_id);
    else if (find_professor(_id) != NULL)
        current_user = find_professor(_id);
    else if (_id == DEFAULT_USER_ID)
        current_user = default_user;
}

vector<string> Handler::login(string id, string password)
{
    if (current_user != NULL)
        throw PermissionExeption();
    vector<string> output;
    if (!is_id_vaild(id))
        throw NotFoundExeption();
    for (auto student : students)
    {
        if (student->get_id() == id)
        {
            if (student->get_password() == password)
            {
                current_user = student;
                output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
            }
            else
                throw PermissionExeption();
        }
    }
    for (auto professor : professors)
    {
        if (professor->get_id() == id)
        {
            if (professor->get_password() == password)
            {
                current_user = professor;
                output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
            }
            else
                throw PermissionExeption();
        }
    }
    if (id == "0")
    {
        if (password == DEFAULT_USER_PASSWORD)
        {
            current_user = default_user;
            output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
        }
        else
            throw PermissionExeption();
    }

    return output;
}

bool Handler::is_id_vaild(string id)
{
    for (auto user : users)
    {
        if (user->get_id() == id)
            return true;
    }
    return false;
}

bool Handler::is_password_vaild(string password)
{
    for (auto user : users)
    {
        if (user->get_password() == password)
            return true;
    }
    return false;
}

bool Handler::is_user_logged_in()
{
    if (current_user != NULL)
        return true;
    return false;
}

vector<string> Handler::logout()
{
    vector<string> output;
    current_user = NULL;
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::add_course(string course_id, string pid, string class_number, string time, string exam_date, string capacity)
{
    vector<string> output;
    Course *the_course = NULL;
    Professor *the_professor = NULL;
    if (!dynamic_cast<Default_user *>(current_user))
    {
        throw PermissionExeption();
    }
    the_course = find_course(course_id);
    the_professor = find_professor(pid);
    if (!is_natural_number(course_id) || !is_natural_number(capacity) || !is_natural_number(class_number))
        throw BadReqExeption();
    if (the_course == NULL || !is_id_vaild(pid))
        throw NotFoundExeption();
    if (the_professor == NULL || !does_professor_present_course(the_professor, the_course))
        throw PermissionExeption();
    vector<string> splited_week_day = split(time, ':');
    vector<string> lecture_time_interval = split(splited_week_day[1], '-');
    Time *the_lecture_time = new Time(stoi(lecture_time_interval[0]), stoi(lecture_time_interval[1]), splited_week_day[0]);
    the_professor->handle_time_for_teaching(the_lecture_time);
    lecture_id_generator++;

    Lecture *the_lecture = new Lecture(the_course, pid, stoi(capacity), the_lecture_time, exam_date, stoi(class_number), lecture_id_generator, the_professor->get_name());
    Channel *the_channel = new Channel(the_professor);
    channel_lecture_interfaces.push_back(new Channel_lecture_interface(the_channel, the_lecture));
    the_professor->add_lecture(the_lecture);
    lectures.push_back(the_lecture);
    for (auto student : students)
        student->add_notification(the_lecture->get_professor_initials() + ": " + ADDED_LECTURE_NOTIFICATION_MESSAGE);
    for (auto professor : professors)
        professor->add_notification(the_lecture->get_professor_initials() + ": " + ADDED_LECTURE_NOTIFICATION_MESSAGE);
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

Professor *Handler::find_professor(string id)
{
    for (auto professor : professors)
        if (professor->get_id() == id)
            return professor;
    return NULL;
}

Student *Handler::find_student(string id)
{
    for (auto student : students)
        if (student->get_id() == id)
            return student;
    return NULL;
}

Course *Handler::find_course(string id)
{
    for (auto course : courses)
    {
        if (course->id == stoi(id))
            return course;
    }
    return NULL;
}

Lecture *Handler::find_lecture(string id)
{
    for (auto lecture : lectures)
    {
        if (lecture->is_lecture_id_equal(id))
            return lecture;
    }
    return NULL;
}

bool Handler::does_professor_present_course(Professor *the_professor, Course *the_course)
{
    for (auto major_id : the_course->majors_id)
    {
        if (the_professor->get_major_id() == major_id)
            return true;
    }
    return false;
}

string Handler::get_courses_in_html()
{
    string output = "";
    for (auto lecture : lectures)
    {
        output += lecture->get_personal_detail_in_html();
    }
    return output;
}
void Handler::set_profile_picture(string image_path)
{
    current_user->add_profile_photo(image_path);
}

string Handler::get_my_courses_in_html()
{
    string output = "";
    if (!dynamic_cast<Student *>(current_user))
    {
        throw PermissionExeption();
    }
    output = dynamic_cast<Student *>(current_user)->get_my_course_in_html();
    return output;
}

vector<string> Handler::get_courses(const vector<string> splitted_req)
{
    vector<string> output;
    if (dynamic_cast<Default_user *>(current_user))
    {
        throw PermissionExeption();
    }
    int arg_counter = 0;
    if (splitted_req.size() == 5)
    {
        if (!is_natural_number(splitted_req[4]))
        {
            throw BadReqExeption();
        }
        if (!is_lecture_id_valid(splitted_req[4]))
        {
            throw NotFoundExeption();
        }
        for (auto lecture : lectures)
        {
            if (lecture->is_lecture_id_equal(splitted_req[4]))
            {
                output.push_back(lecture->get_personal_detail());
            }
        }
    }
    else
    {
        if (lectures.size() == 0)
            throw EmptyExeption();
        for (auto lecture : lectures)
        {
            output.push_back(lecture->get_brief_detail());
        }
    }
    return output;
}

bool Handler::is_lecture_id_valid(string id)
{
    for (auto lecture : lectures)
    {
        if (lecture->is_lecture_id_equal(id))
        {
            return true;
        }
    }
    return false;
}

string Handler::get_detail_in_html(string id)
{
    string output;
    if (!is_natural_number(id) && id != "0")
    {
        throw BadReqExeption();
    }
    bool valid_id = false;
    for (auto user : users)
    {
        if (user->get_id() == id)
        {
            output = user->get_detail_page_in_html();
            valid_id = true;
        }
    }
    if (!valid_id)
        throw NotFoundExeption();
    return output;
}

vector<string> Handler::get_personal_page(string id)
{
    vector<string> output;
    if (!is_natural_number(id) && id != "0")
    {
        throw BadReqExeption();
    }
    bool valid_id = false;
    for (auto user : users)
    {
        if (user->get_id() == id)
        {
            output = user->get_personal_page();
            valid_id = true;
        }
    }

    if (!valid_id)
        throw NotFoundExeption();
    return output;
}

vector<string> Handler::get_post(string id, string post_id)
{
    vector<string> output;
    if (!is_natural_number(post_id))
        throw BadReqExeption();
    if (!is_natural_number(id) && id != "0")
        throw BadReqExeption();
    bool valid_id = false;
    for (auto user : users)
    {
        if (user->get_id() == id)
        {
            valid_id = true;
            output = user->get_post(post_id);
        }
    }
    if (!valid_id || output.empty())
        throw NotFoundExeption();
    return output;
}

vector<string> Handler::add_normal_post(string title, string message, string image_path)
{
    vector<string> output;
    current_user->add_normal_post(title, message, image_path);
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::add_ta_form_post(string lecture_id, string message)
{
    if (!dynamic_cast<Professor *>(current_user))
    {
        throw PermissionExeption();
    }
    vector<string> output;
    if (!is_natural_number(lecture_id))
        throw BadReqExeption();
    if (!is_lecture_id_valid(lecture_id))
        throw NotFoundExeption();
    dynamic_cast<Professor *>(current_user)->add_ta_form_post(lecture_id, message);
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::delete_post(string post_id)
{
    vector<string> output;
    if (!is_natural_number(post_id))
        throw BadReqExeption();
    current_user->delete_post(post_id);
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::add_connect(string id)
{
    vector<string> output;
    if (!is_natural_number(id))
        throw BadReqExeption();
    bool found_id = false;
    for (auto user : users)
    {
        if (user->get_id() == id)
        {
            found_id = true;
        }
    }
    if (!found_id)
        throw NotFoundExeption();
    if (current_user->is_connected(id))
        throw BadReqExeption();
    for (auto user : users)
    {
        if (user->get_id() == id)
        {
            if (current_user == user)
                throw PermissionExeption();
            current_user->add_connect(user);
            user->add_connect(current_user);
        }
    }
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::get_notification()
{
    vector<string> output = current_user->get_notification();
    return output;
}
bool Handler::is_current_user_a_student()
{
    bool is_a_student = false;
    if (dynamic_cast<Student *>(current_user))
    {
        is_a_student = true;
    }
    return is_a_student;
}

vector<string> Handler::register_my_course(string id)
{
    vector<string> output;
    if (!dynamic_cast<Student *>(current_user))
    {
        throw PermissionExeption();
    }
    if (!is_natural_number(id))
        throw BadReqExeption();
    bool found_id = false;
    for (auto interface : channel_lecture_interfaces)
    {
        if (interface->the_lecture->is_lecture_id_equal(id))
        {
            found_id = true;
            Student *the_student = dynamic_cast<Student *>(current_user);
            the_student->register_my_course(interface->the_lecture);
            interface->the_channel->add_member(the_student);
        }
    }
    if (!found_id)
        throw NotFoundExeption();
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::delete_course(string id)
{
    vector<string> output;
    if (!dynamic_cast<Student *>(current_user))
    {
        throw PermissionExeption();
    }
    if (!is_natural_number(id))
        throw BadReqExeption();
    dynamic_cast<Student *>(current_user)->delete_my_course(id);
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::get_my_courses()
{
    vector<string> output;
    if (!dynamic_cast<Student *>(current_user))
    {
        throw PermissionExeption();
    }
    output = dynamic_cast<Student *>(current_user)->get_my_course();
    return output;
}

vector<string> Handler::send_ta_req(string pid, string form_id)
{
    vector<string> output;
    Student *the_student = dynamic_cast<Student *>(current_user);
    if (!the_student)
    {
        throw PermissionExeption();
    }
    if (!is_natural_number(pid))
        throw BadReqExeption();
    if (!find_professor(pid))
        throw NotFoundExeption();
    dynamic_cast<Professor *>(find_professor(pid))->handle_ta_req_from(current_user->get_id(), form_id, the_student->get_semester());
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<Ta_applicant_info *> Handler::close_ta_form_req(string fid)
{
    vector<string> output;
    Professor *the_professor = dynamic_cast<Professor *>(current_user);
    if (!the_professor)
    {
        throw PermissionExeption();
    }
    if (!is_natural_number(fid))
        throw BadReqExeption();
    vector<string> student_ids = the_professor->get_ta_applicants_id(fid);
    vector<Ta_applicant_info *> ta_applicants_info;
    fill_ta_applicant_infos(student_ids, ta_applicants_info);
    return ta_applicants_info;
}

void Handler::fill_ta_applicant_infos(vector<string> student_ids, vector<Ta_applicant_info *> &ta_applicants_info)
{
    for (auto student_id : student_ids)
    {
        Student *the_student = find_student(student_id);
        ta_applicants_info.push_back(new Ta_applicant_info(the_student->get_id(), the_student->get_name(), the_student->get_semester()));
    }
}

void Handler::handle_ta_results(const vector<Ta_applicant_info *> ta_applicants_info, string fid)
{
    for (auto ta_applicant_info : ta_applicants_info)
    {
        if (ta_applicant_info->result == result_ta_req::ACCEPT)
        {
            handle_accepted_result(ta_applicant_info, fid);
        }
        send_ta_result_notification(ta_applicant_info, fid);
    }
}

void Handler::send_ta_result_notification(Ta_applicant_info *ta_applicant_info, string fid)
{
    if (!is_natural_number(fid))
        throw BadReqExeption();
    string lecture_id = find_lecture_id_from_post_form(fid);
    Lecture *the_lecture = find_lecture(lecture_id);
    string notif;
    if (ta_applicant_info->result == result_ta_req::ACCEPT)
        notif = the_lecture->get_id() + " " + the_lecture->get_name() + ": " + ACCEPTED_RESULT_TA_REQ_NOTIFICATION;
    else
        notif = the_lecture->get_id() + " " + the_lecture->get_name() + ": " + REJECTED_RESULT_TA_REQ_NOTIFICATION;
    find_student(ta_applicant_info->student_id)->add_notification(notif);
}

string Handler::find_lecture_id_from_post_form(string fid)
{
    Professor *the_professor = dynamic_cast<Professor *>(current_user);
    if (!the_professor)
    {
        throw PermissionExeption();
    }
    if (!is_natural_number(fid))
        throw BadReqExeption();
    return the_professor->get_lecture_id_by(fid);
}

void Handler::handle_accepted_result(Ta_applicant_info *ta_applicant_info, string fid)
{
    if (!is_natural_number(fid))
        throw BadReqExeption();
    string lecture_id = find_lecture_id_from_post_form(fid);
    for (auto channel_lecture_interface : channel_lecture_interfaces)
    {
        if (channel_lecture_interface->the_lecture->get_id() == lecture_id)
        {
            channel_lecture_interface->the_channel->add_ta(find_student(ta_applicant_info->student_id));
            find_student(ta_applicant_info->student_id)->add_to_mylecture_as_ta(channel_lecture_interface->the_lecture);
        }
    }
}

vector<string> Handler::add_profile_photo(string photo_path)
{
    vector<string> output;
    current_user->add_profile_photo(photo_path);
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::add_course_post(string id, string title, string message, string image_path)
{
    if (!is_natural_number(id))
        throw BadReqExeption();
    if (!find_lecture(id))
        throw NotFoundExeption();
    vector<string> output;
    for (auto channel_lecture_interface : channel_lecture_interfaces)
    {
        if (channel_lecture_interface->the_lecture->get_id() == id)
        {
            channel_lecture_interface->the_channel->add_post(title, message, image_path, current_user->get_id(), channel_lecture_interface->the_lecture->get_id());
            string lecture_id = channel_lecture_interface->the_lecture->get_id();
            string lecture_name = channel_lecture_interface->the_lecture->get_name();
            string notif = lecture_id + " " + lecture_name + ": " + ADDED_COURSE_POST_NOTIFICATION;
            channel_lecture_interface->the_channel->send_notification(current_user->get_id(), notif);
        }
    }
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::get_course_channel(string id)
{
    if (!is_natural_number(id))
        throw BadReqExeption();
    if (!find_lecture(id))
        throw NotFoundExeption();
    vector<string> output;
    for (auto channel_lecture_interface : channel_lecture_interfaces)
    {
        if (channel_lecture_interface->the_lecture->get_id() == id)
        {
            output = channel_lecture_interface->the_channel->get_channel(current_user->get_id());
            output.insert(output.begin(), channel_lecture_interface->the_lecture->get_personal_detail());
        }
    }
    return output;
}

vector<string> Handler::get_course_post(string lecture_id, string post_id)
{
    if (!is_natural_number(lecture_id) || !is_natural_number(post_id))
        throw BadReqExeption();
    if (!find_lecture(lecture_id))
        throw NotFoundExeption();
    vector<string> output;
    for (auto channel_lecture_interface : channel_lecture_interfaces)
    {
        if (channel_lecture_interface->the_lecture->get_id() == lecture_id)
        {
            output.push_back(channel_lecture_interface->the_lecture->get_personal_detail());
            output.push_back(channel_lecture_interface->the_channel->get_post(post_id, current_user->get_id()));
        }
    }
    return output;
}
