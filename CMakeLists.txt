# Minimum CMake version
cmake_minimum_required(VERSION 3.29.0 FATAL_ERROR)

# Project name and language
project(DGE LANGUAGES CXX)

# Add option to enable/disable coverage report
option(DGE_COVERAGE_REPORT "Enable coverage report" OFF)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# GTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip # 1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For windows
FetchContent_MakeAvailable(googletest)

# Compiler version
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Pass only MSVC and Clang as supported compilers
if (NOT MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "Unsupported compiler")
endif ()

# Add flags depending on build configuration
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    message(STATUS "Debug build")
    if (MSVC)
        add_compile_options(/W4 /WX)
    else ()
        add_compile_options(-g -O0 -Wall -Wextra -Werror)
    endif ()
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    message(STATUS "Release build")
    if (MSVC)
        add_compile_options(/O2 /Ob2 /Oi /Ot /Oy /GL)
    else ()
        add_compile_options(-O3)
    endif ()
endif ()

# Coverage report
if (DGE_COVERAGE_REPORT)
    message(STATUS "Coverage report enabled")
    if (MSVC)
        message(FATAL_ERROR "Coverage report is not supported on MSVC")
    else ()
        add_compile_options(--coverage)
        add_link_options(--coverage)
    endif ()
endif ()

# Projects
add_subdirectory(engine)
add_subdirectory(tests)
add_subdirectory(samples)
