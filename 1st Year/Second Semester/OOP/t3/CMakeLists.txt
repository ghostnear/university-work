cmake_minimum_required(VERSION 3.0)

project(Test3)

file(
    GLOB
    PROJECT_SOURCES
    src/*.cpp
    src/domain/*.cpp
    src/service/*.cpp
    src/ui/*.cpp
)

add_executable("${PROJECT_NAME}" ${PROJECT_SOURCES})

target_include_directories(
    "${PROJECT_NAME}"
    PUBLIC
    "include/"
)

find_package(
    Qt6
    COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED
)

target_link_libraries(
    "${PROJECT_NAME}"
    PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)