# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create a project named Tutorial
project(advent-of-code-2020 VERSION 1.0)
# Use configure_file to configure and copy TutorialConfig.h.in to
# TutorialConfig.h
#configure_file(TutorialConfig.h.in TutorialConfig.h)

# Add an executable called Tutorial to the project
add_subdirectory(src)
add_compile_definitions(READ_AOC_INPUT_FROM_CMD)
#add_target_definitions() # for target-by-target macro defs
add_executable(day1 ./src/main/day1.cpp)
target_link_libraries(day1 day1_util)

add_executable(day4 ./src/main/day4.cpp)
target_link_libraries(day4 day4_util)

add_executable(day7 ./src/main/day7.cpp)
target_link_libraries(day7 day7_util)

add_executable(day11 ./src/main/day11.cpp)
target_link_libraries(day11 day1_util)

# Use target_include_directories to include header files
target_include_directories(day1
	PUBLIC "${PROJECT_BINARY_DIR}"
	PUBLIC "${PROJECT_SOURCE_DIR}/include"
	)
