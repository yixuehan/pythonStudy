project(gstreamer)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.1)
add_compile_options(-ggdb)

# include_directories(/usr/include/gstreamer-1.0)
include(FindPkgConfig)
pkg_search_module(GSTREAMER REQUIRED gstreamer-1.0)

message(STATUS "gstreamer include:" ${GSTREAMER_INCLUDE_DIRS})
message(STATUS "gstreamer libs:" ${GSTREAMER_LIBRARIES})

add_executable(first first.cpp)
target_link_libraries(first ${GSTREAMER_LIBRARIES})
target_include_directories(first PUBLIC ${GSTREAMER_INCLUDE_DIRS})

add_executable(rtsp rtsp.cpp)
target_link_libraries(rtsp ${GSTREAMER_LIBRARIES})
target_include_directories(rtsp PUBLIC ${GSTREAMER_INCLUDE_DIRS})

add_executable(make_element make_element.cpp)
target_link_libraries(make_element ${GSTREAMER_LIBRARIES})
target_include_directories(make_element PUBLIC ${GSTREAMER_INCLUDE_DIRS})

add_executable(get_element get_element.cpp)
target_link_libraries(get_element ${GSTREAMER_LIBRARIES})
target_include_directories(get_element PUBLIC ${GSTREAMER_INCLUDE_DIRS})

add_executable(audio audio.cpp)
target_link_libraries(audio ${GSTREAMER_LIBRARIES})
target_include_directories(audio PUBLIC ${GSTREAMER_INCLUDE_DIRS})

add_executable(video_audio video_audio.cpp)
target_link_libraries(video_audio ${GSTREAMER_LIBRARIES})
target_include_directories(video_audio PUBLIC ${GSTREAMER_INCLUDE_DIRS})

add_executable(usb_video usb_video.cpp)
target_link_libraries(usb_video ${GSTREAMER_LIBRARIES})
target_include_directories(usb_video PUBLIC ${GSTREAMER_INCLUDE_DIRS})

add_executable(record_mp4 record_mp4.cpp)
target_link_libraries(record_mp4 ${GSTREAMER_LIBRARIES} pthread)
target_include_directories(record_mp4 PUBLIC ${GSTREAMER_INCLUDE_DIRS})
