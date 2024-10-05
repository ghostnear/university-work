cmake_minimum_required(VERSION 3.0)

project(Assignment45)

file(
    GLOB
    PROJECT_SOURCES
    src/*.cpp
    src/domain/*.cpp
    src/service/*.cpp
    src/ui/*.cpp
)

file(
    GLOB
    PROJECT_TEST_SOURCES
    tests/*.cpp
    ${PROJECT_SOURCES}
)

# Remove main app "main.c" from tests.
list(FILTER PROJECT_TEST_SOURCES EXCLUDE REGEX "/main\\.cpp")

add_executable("${PROJECT_NAME}" ${PROJECT_SOURCES})
add_executable("${PROJECT_NAME}Test" ${PROJECT_TEST_SOURCES})

target_include_directories(
    "${PROJECT_NAME}"
    PUBLIC
    "include/"
)

target_include_directories(
    "${PROJECT_NAME}Test"
    PUBLIC
    "include/"
)
