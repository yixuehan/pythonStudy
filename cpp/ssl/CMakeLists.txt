project(ssl)

add_executable(c_server c_server.cpp)
add_library(c_server ssl crypto pthread)

add_executable(c_client c_client.cpp)
add_library(c_client ssl crypto pthread)
