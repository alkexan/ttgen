project(tests)

find_package (Boost 1.76.0 COMPONENTS unit_test_framework REQUIRED)

set(LexicalTestsSrc LexicalTests.cpp)
add_executable(lexical_test ${LexicalTestsSrc})
target_link_libraries(lexical_test ${Boost_LIBRARIES} ttgen_lib)

add_test(NAME lexical_test COMMAND lexical_test)