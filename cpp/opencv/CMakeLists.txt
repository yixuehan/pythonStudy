project(opencv)

add_compile_options(-std=c++14 -g)
add_executable(cv_camera cv_camera.cpp)
target_link_libraries(cv_camera opencv_imgproc opencv_core opencv_highgui opencv_videoio)
target_include_directories(cv_camera PUBLIC ~/usr/opencv/include/opencv4)
