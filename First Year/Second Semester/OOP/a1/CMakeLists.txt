cmake_minimum_required(VERSION 3.0)

project(Assignment1)

add_compile_options(-Wall -Wextra -Wpedantic -O2)

file(
    GLOB SRCS
    src/*.c src/*.h
)

add_executable(${PROJECT_NAME} ${SRCS})
