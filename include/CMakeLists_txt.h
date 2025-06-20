#pragma once

constexpr const char *CMakeLists_txt = "cmake_minimum_required(VERSION 3.20)\nproject(cci)\n\nset(CMAKE_CXX_STANDARD 23)\nset(CMAKE_CXX_STANDARD_REQUIRED ON)\n\ninclude_directories(include)\n\nfile(GLOB_RECURSE SOURCES src/*.cpp)\nadd_executable(${PROJECT_NAME}nit ${SOURCES})\n";