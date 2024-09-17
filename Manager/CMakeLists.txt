cmake_minimum_required(VERSION 3.28)

set(project_name "Manager")

set (header_files Product.h Recipe.h Functions.h)
set (source_files Product.cpp Recipe.cpp "Functions.cpp")
add_library(${project_name} ${source_files})