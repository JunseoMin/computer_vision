cmake_minimum_required(VERSION 3.0)
project(homework_1)

find_package(OpenCV REQUIRED)

add_executable(bilinear_interpolation bilinear_interpolation.cpp)
target_link_libraries(bilinear_interpolation ${OpenCV_LIBS})
add_executable(rotation rotation.cpp)
target_link_libraries(rotation ${OpenCV_LIBS})

