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

vector<string> Handler::login(const vector<string> splitied_req)
{
    if (current_user != NULL)
        throw PermissionExeption();
    vector<string> output;
    int arg_counter = 0;
    string password, id;
    for (int i = 0; i < splitied_req.size() - 1; i++)
    {
        if (splitied_req[i] == "id")
        {
            arg_counter++;
            id = splitied_req[i + 1];
        }
        if (splitied_req[i] == "password")
        {
            password = splitied_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 2)
        throw BadReqExeption();
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
            {
                throw PermissionExeption();
            }
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
            {
                throw PermissionExeption();
            }
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
        {
            throw PermissionExeption();
        }
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

vector<string> Handler::add_course(const vector<string> splitied_req)
{
    vector<string> output;
    Course *the_course = NULL;
    Professor *the_professor = NULL;
    string course_id, pid, class_number, time, exam_date, capacity;
    int arg_counter = 0;
    if (!dynamic_cast<Default_user *>(current_user))
    {
        throw PermissionExeption();
    }
    for (int i = 0; i < splitied_req.size() - 1; i++)
    {
        if (splitied_req[i] == "course_id")
        {
            course_id = splitied_req[i + 1];
            arg_counter++;
        }
        else if (splitied_req[i] == "professor_id")
        {
            pid = splitied_req[i + 1];
            arg_counter++;
        }
        else if (splitied_req[i] == "capacity")
        {
            capacity = splitied_req[i + 1];
            arg_counter++;
        }
        else if (splitied_req[i] == "time")
        {
            time = splitied_req[i + 1];
            arg_counter++;
        }
        else if (splitied_req[i] == "exam_date")
        {
            exam_date = splitied_req[i + 1];
            arg_counter++;
        }
        else if (splitied_req[i] == "class_number")
        {
            class_number = splitied_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 6)
        throw BadReqExeption();
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
    Lecture *the_lecture = new Lecture(the_course, pid, stoi(capacity),the_lecture_time, exam_date, stoi(class_number), lecture_id_generator, the_professor->get_name());

    the_professor->add_lecture(the_lecture);
    lectures.push_back(the_lecture);
    for (auto student : students)
        student->add_notification(the_lecture->professor_id + " " + the_lecture->professor_name + ": " + ADDED_LECTURE_NOTIFICATION_MESSAGE);
    for (auto professor : professors)
        professor->add_notification(the_lecture->professor_id + " " + the_lecture->professor_name + ": " + ADDED_LECTURE_NOTIFICATION_MESSAGE);
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

Course *Handler::find_course(string id)
{
    for (auto course : courses)
    {
        if (course->id == stoi(id))
            return course;
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

vector<string> Handler::get_courses(const vector<string> splitied_req)
{
    vector<string> output;
    if (dynamic_cast<Default_user *>(current_user))
    {
        throw PermissionExeption();
    }
    int arg_counter = 0;
    if (splitied_req.size() == 5)
    {
        if (splitied_req[3] != "id")
            throw BadReqExeption();
        if (!is_natural_number(splitied_req[4]))
        {
            throw BadReqExeption();
        }
        if (!is_lecture_id_valid(splitied_req[4]))
        {
            throw NotFoundExeption();
        }
        for (auto lecture : lectures)
        {
            if (lecture->id == stoi(splitied_req[4]))
            {
                char space = ' ';
                string one_output = splitied_req[4] + space + lecture->the_course->name + space + to_string(lecture->capacity) + space + lecture->professor_name + space + lecture->lecture_time->get_time_str() + space + lecture->exam_date + space + to_string(lecture->class_number);
                output.push_back(one_output);
            }
        }
    }
    else
    {
        if (lectures.size() == 0)
            throw EmptyExeption();
        for (auto lecture : lectures)
        {
            char space = ' ';
            string one_output = to_string(lecture->id) + space + lecture->the_course->name + space + to_string(lecture->capacity) + space + lecture->professor_name;
            output.push_back(one_output);
        }
    }
    return output;
}

bool Handler::is_lecture_id_valid(string id)
{
    for (auto lecture : lectures)
    {
        if (lecture->id == stoi(id))
        {
            return true;
        }
    }
    return false;
}

vector<string> Handler::get_personal_page(const vector<string> splitied_req)
{
    vector<string> output;
    if (splitied_req[3] != "id")
        throw BadReqExeption();
    if (!is_natural_number(splitied_req[4]) && splitied_req[4] != "0")
    {
        throw BadReqExeption();
    }
    bool valid_id = false;
    for (auto user : users)
    {
        if (user->get_id() == splitied_req[4])
        {
            output = user->get_personal_page();
            valid_id = true;
        }
    }

    if (!valid_id)
        throw NotFoundExeption();
    return output;
}

vector<string> Handler::get_post(const vector<string> splitied_req)
{
    vector<string> output;
    int arg_counter = 0;
    string id, post_id;
    for (int i = 0; i < splitied_req.size() - 1; i++)
    {
        if (splitied_req[i] == "id")
        {
            id = splitied_req[i + 1];
            arg_counter++;
        }
        else if (splitied_req[i] == "post_id")
        {
            post_id = splitied_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 2)
        throw BadReqExeption();
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

vector<string> Handler::add_post(const vector<string> splitied_req)
{
    vector<string> output;
    int arg_counter = 0;
    string title, message;
    for (int i = 0; i < splitied_req.size() - 1; i++)
    {
        if (splitied_req[i] == "title")
        {
            title = splitied_req[i + 1];
            arg_counter++;
        }
        else if (splitied_req[i] == "message")
        {
            message = splitied_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 2)
    {
        throw BadReqExeption();
    }
    current_user->add_post(title, message);
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::delete_post(const vector<string> splitied_req)
{
    vector<string> output;
    int arg_counter = 0;
    string post_id;
    for (int i = 0; i < splitied_req.size() - 1; i++)
    {
        if (splitied_req[i] == "id")
        {
            post_id = splitied_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 1)
        throw BadReqExeption();
    if (!is_natural_number(post_id))
        throw BadReqExeption();
    current_user->delete_post(post_id);
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::add_connect(const vector<string> splitied_req)
{
    vector<string> output;
    int arg_counter = 0;
    string id;
    for (int i = 0; i < splitied_req.size() - 1; i++)
    {
        if (splitied_req[i] == "id")
        {
            id = splitied_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 1)
        throw BadReqExeption();
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
            if(current_user == user)
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

vector<string> Handler::register_my_course(const vector<string> splitied_req)
{
    vector<string> output;
    int arg_counter = 0;
    string id;
    if (!dynamic_cast<Student *>(current_user))
    {
        throw PermissionExeption();
    }
    for (int i = 0; i < splitied_req.size() - 1; i++)
    {
        if (splitied_req[i] == "id")
        {
            id = splitied_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 1)
        throw BadReqExeption();
    if (!is_natural_number(id))
        throw BadReqExeption();
    bool found_id = false;
    for (auto lecture : lectures)
    {
        if (to_string(lecture->id) == id)
        {
            found_id = true;
            dynamic_cast<Student *>(current_user)->register_my_course(lecture);
        }
    }
    if (!found_id)
        throw NotFoundExeption();
    output.push_back(SUCCESSFULLY_FINISHED_REQ_MESSAGE);
    return output;
}

vector<string> Handler::delete_course(const vector<string> splitied_req)
{
    vector<string> output;
    int arg_counter = 0;
    string id;
    if (!dynamic_cast<Student *>(current_user))
    {
        throw PermissionExeption();
    }
    for (int i = 0; i < splitied_req.size() - 1; i++)
    {
        if (splitied_req[i] == "id")
        {
            id = splitied_req[i + 1];
            arg_counter++;
        }
    }
    if (arg_counter != 1)
        throw BadReqExeption();
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
