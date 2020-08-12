project(curl)
add_compile_options(
    -ggdb3
    )

add_executable(test_curl test_curl.cpp)
target_link_libraries(test_curl curl)
