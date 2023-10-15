cmake_minimum_required(VERSION 3.0)
project(beauty_shot)

find_package(OpenCV REQUIRED)

add_executable(beauty_shot src/beauty_shot.cc)
target_link_libraries(beauty_shot ${OpenCV_LIBS})