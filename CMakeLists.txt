cmake_minimum_required(VERSION 2.8.4)
project(CFACC CXX)

set(CFACC_DIR "${CFACC_SOURCE_DIR}")

include("${CFACC_DIR}/cmake/DepsCFACC.txt")
find_package(Doxygen)

include_directories(${ARMADILLO_INCLUDE_DIRS})
include_directories(${CFACC_DIR})
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)
add_executable(cfacc++ src/main.C)
add_dependencies(cfacc++ cfacc)
get_filename_component(ARMADILLO_LIBDIR "${ARMADILLO_LIBRARIES}"
    DIRECTORY)
target_link_libraries(cfacc++ cfacc ${ARMADILLO_LIBRARIES})

if(DOXYGEN_FOUND AND (DOXYGEN_VERSION VERSION_GREATER "1.8"))
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
    add_custom_target(docs
        "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Doxygen documentation" VERBATIM)
endif()
