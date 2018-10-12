cmake_minimum_required(VERSION 3.10)
project(Countdown)

set(SOURCE_FILES countdown.cpp countdown.h)

add_library(countdown STATIC ${SOURCE_FILES})