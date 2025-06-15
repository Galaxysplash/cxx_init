#include "program.hpp"
#include "file.hpp"

#include <iostream>

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
        "build", "src"};

    std::stringstream
        cmakelists_content,
        python_run_file_content,
        readme_file_content,
        dot_gitignore_content,
        conan_file_txt_content;

    std::stringstream
        main_cpp_content;

    main_cpp_content
        << "#include <iostream>\n\n"
        << "int main(int argc, const char* argv[])\n"
        << "{\n"
        << "\tstd::cout << \"Hello World!\\n\";\n\n"
        << "\treturn 0;\n"
        << "}";

    cmakelists_content
        << "cmake_minimum_required(VERSION 3.20)\n"
        << "project(" << project_name << ")\n"
        << "\n"
        << "set(CMAKE_CXX_STANDARD 20)\n"
        << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
        << "\n"
        << "file(GLOB_RECURSE SOURCES src/*.cpp)\n"
        << "add_executable(${PROJECT_NAME} ${SOURCES})\n";

    python_run_file_content
        << "import platform\n"
        << "import subprocess\n\n"
        << "app_name: str = \"" << project_name << "\"\n\n"
        << "if platform.system() == \"Windows\":\n"
        << "\tsubprocess.run(\"rmdir /S /Q build\", shell = True)\n"
        << "else:\n"
        << "\tsubprocess.run(\"rm -rf build\", shell = True)\n\n"
        << "subprocess.run(\"mkdir build\", shell=True)\n\n"
        << "subprocess.run("
        << "f\"" << "conan install . --build=missing -of build "
        << "&& cmake . -B build && make -C build"
        << "\""
        << ", check=True, shell=True)\n\n"
        << "if platform.system() == \"Windows\":\n"
        << "\tsubprocess.run([f\".\\\\build\\\\{app_name}.exe\"], check = True)\n"
        << "else:\n"
        << "\tsubprocess.run([f\"./build/{app_name}\"], check = True)\n";

    readme_file_content
        << "# " << project_name
        << "\n\n"
        << "## prerequisites\n"
        << "->python3<br>\n"
        << "->git<br>\n"
        << "->make<br>\n"
        << "->cmake 3.20 or higher\n\n"
        << "## build & run\n"
        << "-> On Windows: 'python run.py'<br>\n"
        << "-> On unix-like systems like (macOS, Linux, freeBSD, ...): "
        << "'python3 run.py'<br>\n";

    dot_gitignore_content
        << "build\n"
        << ".vscode\n";

    conan_file_txt_content
        << "# uncomment for external dependencies\n"
        << "# [requires]\n\n\n"
        << "[generators]\n"
        << "CMakeDeps\n"
        << "CMakeToolchain\n\n"
        << "[layout]\n"
        << "cmake_layout\n";

    File global_files[] = {
        {"CMakeLists.txt", cmakelists_content.str()},
        {"run.py", python_run_file_content.str()},
        {".gitignore", dot_gitignore_content.str()},
        {"README.md", readme_file_content.str()},
        {"conanfile.txt", conan_file_txt_content.str()}};

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
    std::stringstream first_run_cmd;

#ifdef _WIN32
#define SEPERATOR "\\"

    constexpr auto PYTHON_CMD = "python";
#else
#define SEPERATOR "/"

    constexpr auto PYTHON_CMD = "python3";
#endif
    first_run_cmd
        << PYTHON_CMD
        << " "
        << project_name
        << SEPERATOR
        << "run.py\n";

    system(first_run_cmd.str().c_str());

    std::stringstream
        git_init_cmd,
        git_add_cmd,
        git_commit_cmd;

    git_init_cmd << "git init -C " << project_directory.str() << " --initial-branch=main";
    git_add_cmd << "git add -C " << project_directory.str() << "*";
    git_commit_cmd << "git commit -C " << project_directory.str() << "-a -m \"init\"";

    system(git_init_cmd.str().c_str());
    system(git_add_cmd.str().c_str());
    system(git_commit_cmd.str().c_str());

    std::cout
        << "NOTE: Leave blank for local only.\n\n"
        << "URL: ";

    std::string url = "";
    url.reserve(40);
    std::cin >> url;

    if (
        url != "" and
        url.find(';') == std::string::npos and
        url.find('&') == std::string::npos)
    {
        std::stringstream
            remote_add_cmd,
            git_push_cmd;

        remote_add_cmd << "git -C " << project_directory.str() << " remote add origin " << url;
        git_push_cmd << "git push -C " << project_directory.str() << " -u origin main";

        system(remote_add_cmd.str().c_str());
        system(git_push_cmd.str().c_str());
    }

    std::cout << "\n";

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
