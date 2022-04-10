# Application CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (ttgen CXX)

# Sources files
add_executable (ttgen "Main.cpp")

# Add extern library
target_link_libraries(ttgen ${Boost_LIBRARIES})
target_link_libraries(ttgen tboolean)
target_link_libraries(ttgen util)
target_link_libraries(ttgen lexical_analyzer)
target_link_libraries(ttgen syntax_analyzer)
target_link_libraries(ttgen code_generator)
