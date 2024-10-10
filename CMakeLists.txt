# Minimum CMake version
cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

# Project name and language
project(DGE LANGUAGES CXX)

# Add option to enable/disable coverage report
option(DGE_COVERAGE_REPORT "Enable coverage report" OFF)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GCC >= 14
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14.0)
        message(FATAL_ERROR "GCC version must be at least 14.0")
    endif ()
endif ()

# Clang >= 16
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16.0)
        message(FATAL_ERROR "Clang version must be at least 16.0")
    endif ()
endif ()

# MSVC >= 19.30
if (MSVC)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.30)
        message(FATAL_ERROR "MSVC version must be at least 19.30")
    endif ()
endif ()

# GTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip # 1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For windows
FetchContent_MakeAvailable(googletest)
enable_testing()

# Compiler version
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

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

# When building with Clang, use libc++
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif ()
