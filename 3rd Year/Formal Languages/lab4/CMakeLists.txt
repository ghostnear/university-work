cmake_minimum_required(VERSION 3.5)

project(lab4)

file(
    GLOB_RECURSE
    ${PROJECT_NAME}_SOURCE_FILES
        "src/*.cpp"
)

add_executable(
    ${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCE_FILES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        -pedantic -pedantic-errors -Wextra -Werror
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