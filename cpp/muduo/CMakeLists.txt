add_executable(timer timer.cpp)
target_link_libraries(timer muduo_net muduo_base pthread)
