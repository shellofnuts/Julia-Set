cmake_minimum_required(VERSION 3.22)

project(juliaset)

set(CMAKE_CXX_STANDARD 17)

find_package(freeimage CONFIG REQUIRED)
include_directories(include)

file(GLOB project_SRCS src/*cpp)
add_executable(julia_set ${project_SRCS})
target_link_libraries(julia_set PRIVATE freeimage::FreeImage)