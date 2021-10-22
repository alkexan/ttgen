# Util CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (util CXX)

# Compile library
add_library(util STATIC 
	"Util.hpp"
	"Util.cpp"
 )

# Include folders
target_include_directories(util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
