cmake_minimum_required(VERSION 3.28)

set (project_name "HomeCookingManager")

project(${project_name})

add_subdirectory(Manager)

set (source_files "main.cpp" )

add_executable(${project_name} ${source_files})

target_link_libraries(${project_name} Manager)