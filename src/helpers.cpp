#include "helpers.hpp"

#include <iostream>
#include <sstream>

auto Helpers::check_args(const int argc) -> void
{
    std::stringstream err_msg;

    switch (argc)
    {
    case 2:
        return;
    case 1:
        err_msg
            << "sorry. no project name given.\n"
            << "An example would be 'hello_world'\n"
            << "note, that between 'hello' and 'world' are no spaces only a underscore.\n";
        break;
    default:
        err_msg
            << "too much arguments"
            << "please provide only a project_name\n"
            << "where also no spaces exist between the words,\n"
            << "only underscores.\n";
        break;
    }

    throw std::runtime_error(err_msg.str());
}

auto Helpers::create_file(
    const std::string &project_dir,
    const std::string &file_name,
    const std::string &content) -> void
{
    std::stringstream file_path;
    std::ofstream file_creator;
    file_path << project_dir << "/" << file_name;
    file_creator.open(file_path.str());
    file_creator << content;
    file_creator.close();
}

auto Helpers::create_folder(
    const std::string &project_dir,
    const std::string &folder_name) -> void
{
    std::stringstream stringstream;
    stringstream << project_dir << "/" << folder_name;
    std::filesystem::create_directory(stringstream.str());
}

auto Helpers::get_project_directory(const std::string &project_name) -> std::stringstream
{
    std::stringstream project_directory;
    project_directory << std::filesystem::current_path().c_str() << "/" << project_name;

    return std::move(project_directory);
}

auto Helpers::get_src_directory(const std::stringstream &project_directory) -> std::stringstream
{
    std::stringstream src_directory;
    src_directory << project_directory.str() << "/" << "src";

    return std::move(src_directory);
}

auto Helpers::get_src_directory(const std::string &project_name) -> std::stringstream
{
    std::stringstream src_directory;
    src_directory << get_project_directory(project_name).str() << "/src";

    return std::move(src_directory);
}
