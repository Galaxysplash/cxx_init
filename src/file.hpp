#pragma once

#include <string>
#include <string_view>

struct File
{
    File(const std::string &name, const std::string &content)
        : _name(name), _content(content) {}

    auto get_name() -> const std::string &;
    auto get_content() -> const std::string &;

private:
    const std::string _name;
    const std::string _content;
};