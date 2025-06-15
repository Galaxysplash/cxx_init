#pragma once

#include "helpers.hpp"

struct Program final
{
    static auto execute(const std::string &project_name) -> void;
    static auto create_folders(
        const std::stringstream &project_directory,
        const std::initializer_list<std::string> &folder_names) -> void;
};