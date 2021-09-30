# LexicalAnalyzer CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (lexical_analyzer CXX)

# Compile library
add_library(lexical_analyzer STATIC 
	"LexicalAnalyzer.cpp" 
	"LexicalAnalyzer.hpp"
	 
	)

# Add extern library
target_link_libraries(lexical_analyzer util)

# Include folders
target_include_directories(lexical_analyzer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
