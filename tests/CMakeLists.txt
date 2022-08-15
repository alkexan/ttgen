project(tests)

find_package (Boost 1.76.0 COMPONENTS unit_test_framework REQUIRED)

# Lexical Tests
set(LexicalTestsSrc LexicalTests.cpp)
add_executable(lexical_test ${LexicalTestsSrc})
target_link_libraries(lexical_test ${Boost_LIBRARIES} ttgen_lib)

# Syntax Tests
set(SyntaxTestsSrc SyntaxTests.cpp)
add_executable(syntax_test ${SyntaxTestsSrc})
target_link_libraries(syntax_test ${Boost_LIBRARIES} ttgen_lib)

# Parser Tests
set(ParserTestsSrc ParserTests.cpp)
add_executable(parser_test ${ParserTestsSrc})
target_link_libraries(parser_test ${Boost_LIBRARIES} ttgen_lib)

add_test(NAME lexical_test COMMAND lexical_test)
add_test(NAME syntax_test COMMAND syntax_test)
add_test(NAME parser_test COMMAND parser_test)