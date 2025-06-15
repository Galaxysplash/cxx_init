#pragma once

#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>

struct Helpers final
{
    static auto check_args(const int argc) -> bool;
    static auto create_file(
        const std::string &project_dir,
        const std::string &file_name,
        const std::string &content = "") -> void;

    static auto create_folder(
        const std::string &project_dir,
        const std::string &folder_name) -> void;

    static auto get_project_directory(const std::string &project_name) -> std::stringstream;
    static auto get_src_directory(const std::stringstream &project_directory) -> std::stringstream;
    static auto get_src_directory(const std::string &project_name) -> std::stringstream;
};