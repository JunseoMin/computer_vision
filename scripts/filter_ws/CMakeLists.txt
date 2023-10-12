cmake_minimum_required(VERSION 3.0)
project(filter_ws)

find_package(OpenCV REQUIRED)

add_executable(filter_default src/filter_default.cc)
target_link_libraries(filter_default ${OpenCV_LIBS})

add_executable(filters src/filters.cc)
target_link_libraries(filters ${OpenCV_LIBS})

add_executable(asd src/asd.cc)
target_link_libraries(asd ${OpenCV_LIBS})