cmake_minimum_required(VERSION 3.0)
project(ImageTransformation)

find_package(OpenCV REQUIRED)

add_executable(imageTransformation src/imageTransformation.cc)
target_link_libraries(imageTransformation ${OpenCV_LIBS})