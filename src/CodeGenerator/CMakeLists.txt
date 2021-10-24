# CodeGenerator CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (code_generator CXX)

# Compile library
add_library(code_generator STATIC 
	"CodeGenerator.hpp"
	"CodeGenerator.cpp"
)

# Add extern library
target_link_libraries(code_generator util)
target_link_libraries(code_generator tboolean)

# Include folders
target_include_directories(code_generator PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
