﻿# Application CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (ttgen CXX)

# Sources files
add_executable (ttgen "Main.cpp")

# Add extern library
target_link_libraries(ttgen ${Boost_LIBRARIES})
target_link_libraries(ttgen ttgen_lib)

# installation
install(TARGETS ttgen DESTINATION bin)
