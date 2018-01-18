# Main CMakeLists.txt
cmake_minimum_required(VERSION 3.10.1)
project(circumflex)


# Set constants
set(CMAKE_CXX_STANDARD 17)


# Make executable
add_executable(tests tests.cc)


# Compiler warnings
if (MSVC)
  target_compile_options(tests PRIVATE "/W4")
else()
  target_compile_options(tests PRIVATE "-Wpedantic")
  target_compile_options(tests PRIVATE "-Wall")
  target_compile_options(tests PRIVATE "-Wextra")
endif()


# Includes
include_directories(.)
