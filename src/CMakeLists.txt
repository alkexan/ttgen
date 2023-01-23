# Src CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (ttgen_lib CXX)

find_program(RE2C re2c)
if(RE2C)
	# the depfile parser and ninja lexers are generated using re2c.
	function(re2c IN OUT)
		add_custom_command(
			DEPENDS ${IN} OUTPUT ${OUT} COMMAND ${RE2C} -b -i --no-generation-date --no-version -o ${OUT} ${IN}
		)
	endfunction()
	re2c(${CMAKE_CURRENT_SOURCE_DIR}/LexicalAnalyzer.in.cpp ${CMAKE_CURRENT_SOURCE_DIR}/LexicalAnalyzer.cpp)
else()
	message(WARNING "re2c was not found; changes to src/*.in.cc will not affect your build.")
	set(LexicalAnalyzerSrc "LexicalAnalyzer.cpp")
endif()

# Compile library
add_library(ttgen_lib STATIC 
	"Token.hpp"
	"TBoolean.cpp"
	"TBoolean.hpp"
	"SyntaxAnalyzer.cpp"
	"SyntaxAnalyzer.hpp"
	"Parser.cpp"
	"Parser.hpp"
	"LexicalAnalyzer.cpp"
	"LexicalAnalyzer.hpp"
	"TableCalculator.hpp"
	"TableCalculator.cpp"
 )

# Include folders
target_include_directories(ttgen_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
