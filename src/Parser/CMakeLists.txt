# SyntaxAnalyzer CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (parser CXX)

# Compile library
add_library(parser STATIC 
	"Parser.cpp"
	"Parser.hpp")

# Add extern library
target_link_libraries(parser util)
target_link_libraries(parser tboolean)
target_link_libraries(parser lexical_analyzer)
target_link_libraries(parser syntax_analyzer)
target_link_libraries(parser code_generator)

# Include folders
target_include_directories(parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
