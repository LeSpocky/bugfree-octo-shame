cmake_minimum_required(VERSION 2.8.5)
project(bugfree-octo-shame)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

add_subdirectory( "src" )

# documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        SOURCES ${PROJECT_SOURCE_DIR}/Doxyfile.in
    )
endif(DOXYGEN_FOUND)

# test
enable_testing()
add_subdirectory( "test" )
