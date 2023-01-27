cmake_minimum_required (VERSION 3.16)
project (diff)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-g -O0 -Wall -Wextra -Wpedantic")
set (SOURCES main.cpp diff.cpp rec_desent/language.cpp onegin/oneggin.cpp graphmaker_for_diff/graphmaker.cpp latexmaker_for_diff/latexmaker.cpp optimizator/optimizator.cpp tree/tree.cpp optimizator/pow.cpp)

add_executable (diff ${SOURCES})
include_directories (tree)
include_directories (rec_desent)
include_directories (onegin)
include_directories (graphmaker)
include_directories (latexmaker)
include_directories (optimizator)
