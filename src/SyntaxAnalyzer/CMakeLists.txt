# SyntaxAnalyzer CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (syntax_analyzer CXX)

# Compile library
add_library(syntax_analyzer STATIC 
	"SyntaxAnalyzer.cpp"
	"SyntaxAnalyzer.hpp"
 "AbstractSyntaxTree.hpp")

# Add extern library
target_link_libraries(syntax_analyzer util)

# Include folders
target_include_directories(syntax_analyzer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
