# Src CMakeList.txt
cmake_minimum_required (VERSION 3.12)

# Set language and the project name
project (src CXX)

find_program(RE2C re2c)
if(RE2C)
	# the depfile parser and ninja lexers are generated using re2c.
	function(re2c IN OUT)
		add_custom_command(
			DEPENDS ${IN} OUTPUT ${OUT} COMMAND ${RE2C} -b -i --no-generation-date --no-version -o ${OUT} ${IN}
		)
	endfunction()
	set(LexicalAnalyzerSrc ${PROJECT_BINARY_DIR}/LexicalAnalyzer.cpp)
	re2c(${CMAKE_CURRENT_SOURCE_DIR}/LexicalAnalyzer.in.cpp ${LexicalAnalyzerSrc})
else()
	message(WARNING "re2c was not found; changes to src/*.in.cc will not affect your build.")
	set(LexicalAnalyzerSrc "LexicalAnalyzer.cpp")
endif()

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
	${LexicalAnalyzerSrc}
	"LexicalAnalyzer.hpp"
	"CodeGenerator.hpp"
	"CodeGenerator.cpp"
 )

# Include folders
target_include_directories(src PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
