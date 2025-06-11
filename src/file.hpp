#pragma once

#include <string>
#include <string_view>

struct File
{
    File(const std::string &name, const std::string &content) : _name(name), _content(content) {}
    const std::string &get_name();
    const std::string &get_content();

private:
    const std::string _name;
    const std::string _content;
};