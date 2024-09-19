cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME HomeCookingManager)

project(${PROJECT_NAME})

# Установка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES main.cpp "Functions.cpp")

add_subdirectory(Manager)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Manager)