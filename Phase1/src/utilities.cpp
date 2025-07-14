#include "utilities.hpp"
vector<string> read_from_file_line_by_line(const string path)
{
    ifstream file(path);
    string line;
    vector<string> output;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            output.push_back(line);
        }
    }
    else
    {
        cerr << ERROR_MESSAGE_OPEN_FILE << endl;
        exit(1);
    }
    output.erase(output.begin());
    file.close();
    return output;
}

vector<string> split(string original_command, const char delimeter)
{
    vector<string> splitied_command;
    while (original_command != "")
    {
        string token;
        token = original_command.substr(0, original_command.find(delimeter));
        splitied_command.push_back(token);
        original_command.erase(0, token.size() + 1);
    }
    return splitied_command;
}
bool is_natural_number(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    if (str[0] == '0')
        return false;
    return true;
}