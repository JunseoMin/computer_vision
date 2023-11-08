cmake_minimum_required(VERSION 3.0)
project(NoiseFiltering)

find_package(OpenCV REQUIRED)

add_executable(noisefiltering src/noisefiltering.cc)
target_link_libraries(noisefiltering ${OpenCV_LIBS})