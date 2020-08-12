project(mutex)

add_compile_options(-ggdb3)

add_executable(mtx mtx.cpp)
target_link_libraries(mtx pthread)
