cmake_minimum_required(VERSION 3.1.0)

project(project_gtk)

find_package(PkgConfig)
pkg_search_module(GTK REQURIED gtk+-3.0 IMPORTED_TARGET)

MESSAGE(STATUS ${GTK_LIBRARIES})
MESSAGE(STATUS ${GTK_INCLUDE_DIRS})

add_compile_options(-ggdb3)
include_directories(${GTK_INCLUDE_DIRS})
link_libraries(${GTK_LIBRARIES})

add_executable(window window.cpp)

add_executable(example_0 example_0.cpp)
