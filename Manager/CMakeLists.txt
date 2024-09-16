cmake_minimum_required(VERSION 3.28)

set(project_name "Manager")

set (header_files Manager.h)
set (source_files Product.cpp Ingredient.cpp)
add_library(${project_name} ${source_files})