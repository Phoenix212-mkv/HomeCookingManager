cmake_minimum_required(VERSION 3.28)

set(project_name "Manager")



set (header_files Manaher.h)
set (source_files Product.cpp Recipe.cpp  RecipeBook.cpp Inventory.cpp Manager.cpp ProductDatabase.cpp)
add_library(${project_name} ${source_files})