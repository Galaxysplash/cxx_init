#include "helpers.hpp"

#include <iostream>
#include <sstream>

bool Helpers::check_args(const int argc)
{
    switch (argc)
    {
    case 1:
        std::cout << "sorry. no project name given.\n"
                  << "An example would be 'hello_world'\n"
                  << "note, that between 'hello' and 'world' are no spaces only a underscore.\n";
        break;
    case 2:
        return true;
        break;
    default:
        std::cout << "please provide only a project_name\n"
                  << "where also no spaces exist between the words,\n"
                  << "only underscores.\n";
        break;
    }

    return false;
}

void Helpers::create_file(
    const std::string &project_dir,
    const std::string &file_name,
    const std::string &content)
{
    std::stringstream file_path;
    std::ofstream file_creator;
    file_path << project_dir << "/" << file_name;
    file_creator.open(file_path.str());
    file_creator << content;
    file_creator.close();
}

void Helpers::create_folder(
    const std::string &project_dir,
    const std::string &folder_name)
{
    std::stringstream stringstream;
    stringstream << project_dir << "/" << folder_name;
    std::filesystem::create_directory(stringstream.str());
}

std::stringstream Helpers::get_project_directory(const std::string &project_name)
{
    std::stringstream project_directory;
    project_directory << std::filesystem::current_path().c_str() << "/" << project_name;

    return project_directory;
}

std::stringstream Helpers::get_src_directory(const std::string &project_name)
{
    std::stringstream src_directory;
    src_directory << get_project_directory(project_name).str() << "/src";

    return src_directory;
}
