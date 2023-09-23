cmake_minimum_required(VERSION 3.0)
project(homework_1)

find_package(OpenCV REQUIRED)

add_executable(homework_1 homework_1.cpp)
target_link_libraries(homework_1 ${OpenCV_LIBS})
add_executable(homework_1_2 homework_1_2.cpp)
target_link_libraries(homework_1_2 ${OpenCV_LIBS})

