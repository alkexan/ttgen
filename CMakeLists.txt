# Main CMakeList.txt
cmake_minimum_required(VERSION 3.12)

# set language and the project name
project (ttgen_project CXX)

# generate version
exec_program("git" "${PROJECT_SOURCE_DIR}" ARGS "describe" "--tags" OUTPUT_VARIABLE VERSION )
message(STATUS "Version build: " ${VERSION} )
configure_file("version.h.in" "${PROJECT_BINARY_DIR}/version.h")
include_directories(${PROJECT_BINARY_DIR})

# CXX standart
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

# Set compilers options
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Compiler - Microsoft Visual Studio (microsoft.com)")
        set(CXX_FLAGS_COMPILER "/W4 /Wall /WX")
        set(CXX_FLAGS_LINKER "")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Compiler - GNU Compiler Collection (gcc.gnu.org)")
        set(CXX_FLAGS_COMPILER "-Wall -Werror -pedantic")
        set(CXX_FLAGS_LINKER ${CXX_FLAGS_COMPILER})
    endif()

    set(CXXFLAGS ${CXX_FLAGS_COMPILER})
    set(CMAKE_EXE_LINKER_FLAGS_INIT  ${CXX_FLAGS_LINKER})
endif()

# boost package
find_package(Boost 1.76.0 COMPONENTS program_options REQUIRED)
message(STATUS "${Boost_LIBRARIES}")

# generate documetation
if (GENERATE_DOC_DOXY)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
        message(STATUS "Doxygen found - Reference manual will be created")
        add_custom_target(doc_dox ALL Doxygen::doxygen ${PROJECT_SOURCE_DIR}/Doxyfile)
    else (DOXYGEN_FOUND)
        message(STATUS "WARNING: Doxygen not found - Reference manual will not be created")
    endif (DOXYGEN_FOUND)
endif (GENERATE_DOC_DOXY)

include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})

# include subprojects
add_subdirectory (app)
add_subdirectory (src)

# tests
enable_testing ()
add_subdirectory(tests)

# cpack
include(CPack)
set(CPACK_PACKAGE_NAME "ttgen")
set(CPACK_SET_DESTDIR ON)
set(CPACK_PACKAGE_VERSION "${VERSION}") 
set(CPACK_PACKAGE_DESCRIPTION "The Truth Table Generator")
