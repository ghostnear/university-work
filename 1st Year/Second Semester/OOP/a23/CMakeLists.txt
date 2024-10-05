cmake_minimum_required(VERSION 3.0)

project(Assignment23)

add_compile_options(-Wall -g -O2)

file(
    GLOB
    PROJECT_SOURCES
    src/*.c
)

file(
    GLOB
    PROJECT_TEST_SOURCES
    tests/*.c
    ${PROJECT_SOURCES}
)

# Remove main app "main.c" from tests.
list(FILTER PROJECT_TEST_SOURCES EXCLUDE REGEX "/main\\.c")

add_executable("${PROJECT_NAME}" ${PROJECT_SOURCES})
add_executable("${PROJECT_NAME}Test" ${PROJECT_TEST_SOURCES})
