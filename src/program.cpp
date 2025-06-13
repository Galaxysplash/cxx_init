#include "program.hpp"
#include "file.hpp"

#include <iostream>

void Program::execute(const std::string &project_name)
{
    std::stringstream project_directory;
    const auto path_above_project = std::filesystem::current_path();
    project_directory << path_above_project.c_str() << "/" << project_name;
    std::filesystem::create_directory(project_directory.str());
    const std::string folder_names[] = {
        "build", "src"};

    for (const std::string &folder_name : folder_names)
    {
        Helpers::create_folder(project_directory.str(), folder_name);
    }

    std::stringstream
        cmakelists_content,
        python_build_file_content,
        readme_file_content,
        dot_gitignore_content,
        conan_file_txt;

    cmakelists_content << "cmake_minimum_required(VERSION 3.20)\n"
                       << "project(" << project_name << ")\n"
                       << "\n"
                       << "set(CMAKE_CXX_STANDARD 20)\n"
                       << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
                       << "\n"
                       << "file(GLOB_RECURSE SOURCES src/*.cpp)\n"
                       << "add_executable(${PROJECT_NAME} ${SOURCES})\n";

    python_build_file_content << "import platform\n"
                              << "import subprocess\n\n"
                              << "app_name: str = \"" << project_name << "\"\n\n"
                              << "if platform.system() == \"Windows\":\n"
                              << "\tsubprocess.run(\"rmdir /S /Q build\", shell = True)\n"
                              << "else:\n"
                              << "\tsubprocess.run(\"rm -rf build\", shell = True)\n\n"
                              << "subprocess.run("
                              << "\""
                              << "conan install.--build = missing && "
                              << "cmake -B build -D CMAKE_TOOLCHAIN_FILE "
                              << "= build/Release/generators/conan_toolchain.cmake "
                              << "-D CMAKE_BUILD_TYPE = Release && "
                              << "cmake-- build build"
                              << "\""
                              << ", shell=True)\n\n"
                              << "if platform.system() == \"Windows\":\n"
                              << "\tsubprocess.run([f\".\\build\\{app_name}.exe\"], check = True)\n"
                              << "else:\n"
                              << "\tsubprocess.run([f\"./build/{app_name}\"], check = True)\n";

    readme_file_content << "# " << project_name
                        << "\n\n"
                        << "## prerequisites\n"
                        << "->python3<br>\n"
                        << "->git<br>\n"
                        << "->make<br>\n"
                        << "->cmake 3.20 or higher\n\n"
                        << "## build\n"
                        << "-> On Windows: 'python build.py'<br>\n"
                        << "-> On unix-like systems like (macOS, Linux, freeBSD, ...): "
                        << "'python3 build.py'<br>\n";

    dot_gitignore_content << "build\n"
                          << ".vscode\n";

    conan_file_txt << "[requires]\n"
                   << "glew/2.2.0\n"
                   << "glfw/3.4\n"
                   << "glm/1.0.1\n\n"
                   << "[generators]\n"
                   << "CMakeDeps\n"
                   << "CMakeToolchain\n\n"
                   << "[layout]\n"
                   << "cmake_layout\n";

    File global_files[] = {
        {"CMakeLists.txt", cmakelists_content.str()},
        {"build.py", python_build_file_content.str()},
        {".gitignore", dot_gitignore_content.str()},
        {"README.md", readme_file_content.str()},
        {"conanfile.txt", conan_file_txt.str()}};

    for (File &global_file : global_files)
    {
        Helpers::create_file(project_directory.str(), global_file.get_name(), global_file.get_content());
    }

    std::stringstream src_directory;
    src_directory << project_directory.str() << "/src";
    std::stringstream main_cpp_content;

    main_cpp_content << "#include <iostream>\n\n"
                     << "int main(int argc, const char* argv[])\n"
                     << "{\n"
                     << "\tstd::cout << \"Hello World!\\n\";\n\n"
                     << "\treturn 0;\n"
                     << "}";

    File src_file = {"main.cpp", main_cpp_content.str()};
    Helpers::create_file(src_directory.str(), src_file.get_name(), src_file.get_content());
}