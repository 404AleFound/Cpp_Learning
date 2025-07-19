cmake_minimum_required(VERSION 3.10)
project(CPP_U13_project)

file(GLOB SOURCES CONFIGURE_DEPENDS 
    "./code-list-13-*.cpp"
    "./code-list-13-*.h"
)

add_executable(CPP_U13_project ${SOURCES})

target_include_directories(CPP_U13_project PRIVATE examples)


