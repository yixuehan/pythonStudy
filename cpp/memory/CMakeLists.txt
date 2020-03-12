project(memory)

add_executable(cpu_memory cpu_memory.cpp)
target_link_libraries(cpu_memory boost_timer)

add_executable(out_order out_order.cpp)
target_link_libraries(out_order boost_timer pthread)

add_executable(performance performance.cpp)
target_link_libraries(performance boost_timer pthread)

add_executable(shared_ptr shared_ptr.cpp)
target_link_libraries(shared_ptr boost_timer)
