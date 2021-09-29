# Tboolean CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (tboolean CXX)

# Compile library
add_library(tboolean STATIC 
	"TBoolean.cpp"
	"TBoolean.hpp"
)

# Include folders
target_include_directories(tboolean PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
