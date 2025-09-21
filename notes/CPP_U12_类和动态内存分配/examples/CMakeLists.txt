cmake_minimum_required(VERSION 3.10)
project(CPP_U12_project)

file(GLOB SOURCES CONFIGURE_DEPENDS 
    "./code-list-12-*.cpp"
    "./code-list-12-*.h"
)

add_executable(CPP_U12_project ${SOURCES})

target_include_directories(CPP_U12_project PRIVATE examples)


