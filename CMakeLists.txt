cmake_minimum_required (VERSION 3.16)
project (diff)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-g -O0 -Wall -Wextra -Werror -Wpedantic")
set (SOURCES main.cpp diff.cpp rec_cum/language.cpp onegin/oneggin.cpp)

add_executable (diff ${SOURCES})
include_directories (tree)
include_directories (rec_cum)
include_directories (onegin)
