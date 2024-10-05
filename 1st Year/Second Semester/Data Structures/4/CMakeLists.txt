cmake_minimum_required(VERSION 3.0)

project(ADTSortedMap)

file(
    GLOB
    SRCS
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})

target_compile_options(${PROJECT_NAME} PUBLIC -g -O3)