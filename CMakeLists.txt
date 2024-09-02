cmake_minimum_required(VERSION 3.28)

set (projectName "HomeCookingManager")

project(${projectName})

add_subdirectory(Product)

set (source_files "main.cpp")

add_executable(${projectName} ${source_files})

target_link_libraries(${projectName} Product)