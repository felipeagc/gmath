cmake_minimum_required(VERSION 3.10)
project(gmath)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_library(gmath INTERFACE)
target_include_directories(gmath INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(gmath INTERFACE m)

option(GMATH_BUILD_TESTS "Build the gmath tests" ON)
if(GMATH_BUILD_TESTS)
  add_subdirectory(tests)
endif()
