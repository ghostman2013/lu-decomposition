cmake_minimum_required(VERSION 3.9)

project(lud)
set (CMAKE_CXX_STANDARD 11)
find_package(OpenMP REQUIRED)
add_executable(${PROJECT_NAME}
    "main.cpp"
    "matrix.hpp"
    "matrix.cpp"
    "lud.hpp"
    "lud.cpp" )
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
