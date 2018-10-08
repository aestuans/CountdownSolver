cmake_minimum_required(VERSION 3.10)
project(Countdown)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

add_executable(countdown_run ${SOURCE_FILES})

add_subdirectory(countdown)
add_subdirectory(countdown_tests)

target_link_libraries(countdown_run countdown)
