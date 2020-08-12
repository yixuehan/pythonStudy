cmake_minimum_required(VERSION 3.1.0)

project(project_gtk)

find_package(PkgConfig)
pkg_search_module(GTK REQURIED gtk+-3.0 IMPORTED_TARGET)

MESSAGE(STATUS ${GTK_LIBRARIES})
MESSAGE(STATUS ${GTK_INCLUDE_DIRS})

# include_directories(${GTK_INCLUDE_DIRS})
# link_directories(${GTK_LIBRARIES})

add_executable(window window.cpp)
target_link_libraries(window PkgConfig::GTK)

