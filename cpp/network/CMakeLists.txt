project("asio")

add_executable(day_time_server day_time_server.cpp)
target_link_libraries(day_time_server pthread)

add_executable(day_time_client day_time_client.cpp)
target_link_libraries(day_time_client pthread)
