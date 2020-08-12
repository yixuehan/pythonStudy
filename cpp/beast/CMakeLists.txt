project(http)
# set(CXXFLAGS
# -std=c++20
# )
add_compile_options(-std=c++1z -g)
add_executable(http_server main.cpp http_server.cpp parser.cpp json_convert.cpp)
target_link_libraries(http_server binocularLocate pthread)
