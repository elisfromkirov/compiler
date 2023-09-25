cmake_minimum_required(VERSION 3.21)
project(compiler)

include(cmake/build_options.cmake)
include(cmake/compile_options.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../")

if(BUILD_WITH_BENCH)
    add_subdirectory(bench)
endif()

if(BUILD_WITH_SAMPLE)
    add_subdirectory(sample)
endif()

add_subdirectory(source)

if(BUILD_WITH_TEST)
    add_subdirectory(test)
endif()

add_subdirectory(third_party)
