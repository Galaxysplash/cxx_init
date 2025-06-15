#include "file.hpp"
#include "helpers.hpp"
#include "program.hpp"

#include <iostream>

auto main(int argc, const char **argv) -> int
{
    try
    {
        Helpers::check_args(argc);
        Program::execute(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "C++ Fatal: " << e.what() << '\n';
    }

    return 0;
}
