#include "file.hpp"

auto File::get_name() -> const std::string &
{
    return _name;
}

auto File::get_content() -> const std::string &
{
    return _content;
}