cmake_minimum_required(VERSION 3.0)

project(ADTQueue)

file(
    GLOB
    SRCS
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})