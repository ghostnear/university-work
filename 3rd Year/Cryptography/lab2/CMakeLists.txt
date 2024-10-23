cmake_minimum_required(VERSION 3.5)

project(lab2)

file(
    GLOB_RECURSE
    ${PROJECT_NAME}_SOURCE_FILES
        "src/*.c"
)

add_executable(
    ${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCE_FILES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        -Wall -pedantic -pedantic-errors -Wextra
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        "inc/"   
)

install(
    TARGETS
    ${PROJECT_NAME}
)