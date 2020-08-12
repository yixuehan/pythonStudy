project(sqlite3)
set(CMAKE_CXX_COMPILER_ARG1 "-O3")
add_executable(performance performance.cpp)
target_link_libraries(performance sqlite3 boost_timer)
