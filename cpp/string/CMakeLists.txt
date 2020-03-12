cmake_minimum_required(VERSION 3.11)

project(string VERSION 1.0
               DESCRIPTION "STRING"
               LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
add_executable(copy copy.cpp)
add_executable(file file.cpp)
add_executable(json json.cpp)
add_executable(regex regex.cpp)
add_executable(str str.cpp)

add_executable(view view.cpp)
target_link_libraries(view PUBLIC boost_timer)
