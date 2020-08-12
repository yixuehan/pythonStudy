cmake_minimum_required(VERSION 3.16)
project(zip)
add_library(compress STATIC compress.cpp)
target_link_libraries(compress libzip.a libboost_filesystem.a)
add_custom_target(tmp ALL
    COMMAND ${CMAKE_AR} rc /home/shenlan/usr/boost/lib/libboost_filesystem.a /home/shenlan/usr/zip/lib/libzip.a $<TARGET_FILE:compress>)
add_executable(zip compress.cpp zip.cpp)
target_link_libraries(zip libzip.a libboost_filesystem.a)
# target_link_libraries(zip libcompress.a)
