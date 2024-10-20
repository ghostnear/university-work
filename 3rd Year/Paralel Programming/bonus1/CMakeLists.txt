cmake_minimum_required(VERSION 3.5)

project(bonus1)

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
        -Wall -pedantic -pedantic-errors -Wextra -Wcast-align
        -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization
        -Werror -Wfloat-equal -Wformat -Wformat=2 -Wformat-nonliteral -Wformat-security
        -Wformat-y2k -Wimport -Winit-self -Winline -Winvalid-pch -Wwrite-strings
        -Wlong-long -Wmissing-braces -Wmissing-noreturn -Wmissing-field-initializers
        -Wmissing-format-attribute -Wmissing-include-dirs -Wpacked -Wpadded -Wparentheses
        -Wpointer-arith -Wredundant-decls -Wreturn-type -Wvolatile-register-var
        -Wsequence-point -Wshadow -Wsign-compare -Wstack-protector -Wunused-parameter
        -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default -Wunused
        -Wswitch-enum -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunreachable-code
        -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvariadic-macros
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