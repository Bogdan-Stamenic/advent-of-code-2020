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

# Add executables called dayX to the project
add_subdirectory(src)
add_compile_definitions(READ_AOC_INPUT_FROM_CMD)
#add_target_definitions() # for target-by-target macro defs

# O3 optimized binaries
add_executable(day1 ./src/main/day1.cpp)
target_compile_options(day1 PUBLIC -O3) 
target_link_libraries(day1 day1_util)

add_executable(day2 ./src/main/day2.cpp)
target_compile_options(day2 PUBLIC -O3) 
target_link_libraries(day2 day2_util)

add_executable(day3 ./src/main/day3.cpp)
target_compile_options(day3 PUBLIC -O3) 
target_link_libraries(day3 day3_util)

add_executable(day4 ./src/main/day4.cpp)
target_compile_options(day4 PUBLIC -O3) 
target_link_libraries(day4 day4_util)

add_executable(day5 ./src/main/day5.cpp)
target_compile_options(day5 PUBLIC -O3) 
target_link_libraries(day5 day5_util)

add_executable(day6 ./src/main/day6.cpp)
target_compile_options(day6 PUBLIC -O3) 
target_link_libraries(day6 day6_util)

add_executable(day7 ./src/main/day7.cpp)
target_compile_options(day7 PUBLIC -O3) 
target_link_libraries(day7 day7_util)

add_executable(day8 ./src/main/day8.cpp)
target_compile_options(day8 PUBLIC -O3) 
target_link_libraries(day8 day8_util)

add_executable(day9 ./src/main/day9.cpp)
target_compile_options(day9 PUBLIC -O3) 
target_link_libraries(day9 day9_util)

add_executable(day10 ./src/main/day10.cpp)
target_compile_options(day10 PUBLIC -O3) 
target_link_libraries(day10 day10_util)

add_executable(day11 ./src/main/day11.cpp)
target_compile_options(day11 PUBLIC -O3) 
target_link_libraries(day11 day11_util)

add_executable(day12 ./src/main/day12.cpp)
target_compile_options(day12 PUBLIC -O3) 
target_link_libraries(day12 day12_util)

add_executable(day13 ./src/main/day13.cpp)
target_compile_options(day13 PUBLIC -O3) 
target_link_libraries(day13 day13_util)

# Use target_include_directories to include header files
target_include_directories(day1
	PUBLIC "${PROJECT_BINARY_DIR}"
	PUBLIC "${PROJECT_SOURCE_DIR}/include"
	)
