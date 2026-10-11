cmake_minimum_required(VERSION 4.4)

project(cfdlib
    LANGUAGES CXX
    VERSION 0.1.0
    DESCRIPTION "A CFD library."
)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
include(cmake/build_type.cmake)
include(cmake/base.cmake)

add_subdirectory(src)
add_subdirectory(app)
