# Minimum CMake version
cmake_minimum_required(VERSION 3.29.0)

# Project name and language
project(DGE LANGUAGES CXX)

# Allow only MSVC compiler
if(NOT MSVC)
	message(FATAL_ERROR "Only MSVC compiler is supported")
endif()

# Allow only VisualStudio 2022 (v17.0)
# https://cmake.org/cmake/help/latest/variable/MSVC_VERSION.html
if(NOT MSVC_VERSION GREATER_EQUAL 1929)
	message(FATAL_ERROR "Only VisualStudio 2022 is supported")
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Set MSVC tool dir
# Its a hack to extract STL modules & compile them with project
# This is intended to be a temporary solution
set(VCToolsInstallDir "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC") # A possible child can be: /14.41.34120
file(GLOB VCToolsInstallDir "${VCToolsInstallDir}/*")                                          # But using this, we can generalize
list(GET VCToolsInstallDir 0 VCToolsInstallDir)                                                # and allow any version of MSVC (2022)

enable_testing()

# Projects
add_subdirectory(engine)
add_subdirectory(tests)
add_subdirectory(samples)
