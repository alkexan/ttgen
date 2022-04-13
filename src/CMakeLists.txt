# Src CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (src CXX)

# Compile library
add_library(src STATIC 
	"Util.hpp"
	"Util.cpp"
	"TBoolean.cpp"
	"TBoolean.hpp"
	"SyntaxAnalyzer.cpp"
	"SyntaxAnalyzer.hpp"
	"Parser.cpp"
	"Parser.hpp"
	"LexicalAnalyzer.cpp" 
	"LexicalAnalyzer.hpp"
	"CodeGenerator.hpp"
	"CodeGenerator.cpp"
 )

# Include folders
target_include_directories(src PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
