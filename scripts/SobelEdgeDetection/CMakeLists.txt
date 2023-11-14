cmake_minimum_required(VERSION 3.0)
project(SobelEdgeDetection)

find_package(OpenCV REQUIRED)

add_executable(edgedetection src/edgedetection.cc)
target_link_libraries(edgedetection ${OpenCV_LIBS})