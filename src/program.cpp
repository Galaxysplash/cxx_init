#include "program.hpp"
#include "file.hpp"

#include <iostream>

// generated headers
#include <conanfile_txt.h>
#include <dot_gitignore.h>
// end generated headers

auto Program::execute(
    const std::string &project_name) -> void
{
    const std::stringstream &project_directory = Helpers::get_project_directory(project_name);

    pre_setup(project_directory);
    setup(project_name, project_directory);
    post_setup(project_name, project_directory);
}

auto Program::pre_setup(
    const std::stringstream &project_directory) -> void
{
    std::filesystem::remove_all(project_directory.str());
}

auto Program::setup(
    const std::string &project_name,
    const std::stringstream &project_directory) -> void
{
    const std::stringstream &src_directory = Helpers::get_src_directory(project_directory);

    const std::initializer_list<std::string> folder_names = {
        "build", "src", "testing", "include"};

    std::stringstream
        cmakelists_content,
        python_run_file_content,
        readme_file_content,
        dot_gitignore_content,
        conanfile_txt_content;

    std::stringstream
        main_cpp_content;
    {
        cmakelists_content << "cmake_minimum_required(VERSION 3.20)\nproject(" << project_name << ")\n\nset(CMAKE_CXX_STANDARD 23)\nset(CMAKE_CXX_STANDARD_REQUIRED ON)\n\ninclude_directories(include)\n\nfile(GLOB_RECURSE SOURCES src/*.cpp)\nadd_executable(${PROJECT_NAME}nit ${SOURCES})\n";
        main_cpp_content
            << "#include <iostream>\n\n"
            << "auto main(int argc, const char* argv[]) -> int\n"
            << "{\n"
            << "\tstd::cout << \"Hello World!\\n\";\n"
            << "}";

        python_run_file_content << "import os\nimport platform\nfrom subprocess import run, PIPE\n\n# how your executable should be named\nproject_name: str = \"" << project_name << "\"\n\n# arguments you wonna use for testing\ntesting_arguments = \"\"\n\n\n# build code (don't touch it, unless you know what your doing)\nwindows: bool = platform.system() == \"Windows\"\n\nif windows:\n\trun(\"rmdir /S /Q build\", shell = True)\nelse:\n\trun(\"rm -rf build\", shell = True)\n\nif not os.path.exists(\"build\"):\n\trun(\"mkdir build\", shell=True)\n\ndef execute_cmd(cmd: str, description: str):\n\tconan_result = run(\n\t\tcmd,\n\t\tshell=True,\n\t\tstdout=PIPE,\n\t\tstderr=PIPE\n\t)\n\n\tif conan_result.returncode == 0:\n\t\tprint(description + \" was successful!!!\\n\\n\\n\")\n\telse:\n\t\tprint(\"---DETAIL ZONE---\")\n\t\tif conan_result.stdout:\n\t\t\tprint(conan_result.stdout)\n\t\tif conan_result.stderr:\n\t\t\tprint(conan_result.stderr)\n\t\tprint(\"---END DETAIL ZONE---\")\n\t\t\n\t\tprint(\"\\n\\n\\n\" + description + \" has failed! (details are above)\")\n\t\texit(1)\n\n\n\ncmds = [\n\t\t\t(\n\t\t\t\t\"conan install . --build=missing -of build\",\n\t\t\t\t\"Conan installing packages required by your conanfile.txt\"\n\t\t\t),\n\t\t\t(\n\t\t\t\t\"cmake . -B build\",\n\t\t\t\t\"CMake pre generating the stuff necessary for building your project\"\n\t\t\t),\n\t\t\t(\n\t\t\t\t\"make -C build\",\n\t\t\t\t\"Make trying to build your project form the cmake generated stuff\"\n\t\t\t)\n\t\t]\n\nfor cmd in cmds:\n\texecute_cmd(cmd[0], cmd[1])\n\nif windows:\n\tif os.path.exists(f\".\\\\build\\\\{project_name}_exec.exe\"):\n\t\trun([f\".\\\\build\\\\{project_name}_exec.exe {testing_arguments}\"], shell=True, check = True)\nelse:\n\tif os.path.exists(f\"./build/{project_name}_exec\"):\n\t\trun([f\"./build/{project_name}_exec {testing_arguments}\"], shell=True, check = True)\n# end building code";

        readme_file_content
            << "# " << project_name << "\n\n## prerequisites\n->python3<br>\n->git<br>\n->make<br>\n->conan\n->cmake 3.20 or higher\n->vscode\n\n## build & run\n-> On Windows: 'python run.py'<br>\n-> On unix-like systems like (macOS, Linux, ...):'python3 run.py'<br>\n";

        dot_gitignore_content
            << dot_gitignore;

        conanfile_txt_content << conanfile_txt;
    }
    File global_files[] = {
        {"CMakeLists.txt", cmakelists_content.str()},
        {"run.py", python_run_file_content.str()},
        {".gitignore", dot_gitignore_content.str()},
        {"README.md", readme_file_content.str()},
        {"conanfile.txt", conanfile_txt_content.str()}};

    File src_file =
        {"main.cpp", main_cpp_content.str()};

    create_folders(project_directory, folder_names);

    for (File &global_file : global_files)
    {
        Helpers::create_file(project_directory.str(), global_file.get_name(), global_file.get_content());
    }

    Helpers::create_file(src_directory.str(), src_file.get_name(), src_file.get_content());
}

auto Program::post_setup(
    const std::string &project_name,
    const std::stringstream &project_directory) -> void
{
    std::stringstream open_cmd;

    open_cmd << "code " << project_name << "\n";
    system(open_cmd.str().c_str());
}

auto Program::create_folders(
    const std::stringstream &project_directory,
    const std::initializer_list<std::string> &folder_names) -> void
{
    std::filesystem::create_directory(project_directory.str());

    for (const std::string &folder_name : folder_names)
    {
        Helpers::create_folder(project_directory.str(), folder_name);
    }
}
