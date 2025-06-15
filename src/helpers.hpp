#pragma once

#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>

struct Helpers final
{
    static bool check_args(const int argc);
    static void create_file(
        const std::string &project_dir,
        const std::string &file_name,
        const std::string &content = "");

    static void create_folder(
        const std::string &project_dir,
        const std::string &folder_name);

    static std::stringstream get_project_directory(const std::string &project_name);
    static std::stringstream get_src_directory(const std::string &project_name);
};