#include "includes.hpp"
#include "system.hpp"
void running_program(int argc, char *argv[])
{
    vector<string> file_paths;
    for (int i = 1; i < argc; i++)
    {
        file_paths.push_back(argv[i]);
    }
    Handler handler(file_paths);
    System system(&handler);
    system.run();
}

int main(int argc, char *argv[])
{
    running_program(argc, argv);
    return 0;
}