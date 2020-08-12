project(spdlog)

add_executable(spdlog spdlog.cpp)
target_link_libraries(spdlog -lspdlog pthread)

add_executable(fmt fmt.cpp)
target_link_libraries(fmt -lfmt)
