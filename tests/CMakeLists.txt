#set(SRC_AUX)
#add_library(qints_testaux ${SRC_AUX})
target_link_libraries(cfacc)

set(TESTS
    test_test
)
foreach(TEST ${TESTS})
    add_executable(${TEST} ${TEST}.C)
endforeach()

include_directories(${CFACC_DIR})

if(OPENMP_FOUND)
    set(TESTS_COMPILE_FLAGS ${OpenMP_CXX_FLAGS})
    set(TESTS_LINK_FLAGS ${OpenMP_CXX_FLAGS})
endif(OPENMP_FOUND)
foreach(TEST ${TESTS})
    set_target_properties(${TEST} PROPERTIES
        COMPILE_FLAGS "${TESTS_COMPILE_FLAGS}"
        LINK_FLAGS "${TESTS_LINK_FLAGS}"
        BUILD_WITH_INSTALL_RPATH TRUE INSTALL_RPATH_USE_LINK_PATH TRUE)
    if(APPLE)
        get_filename_component(ARMADILLO_LIBDIR "${ARMADILLO_LIBRARIES}"
            DIRECTORY)
        set_target_properties(${TEST} PROPERTIES
            MACOSX_RPATH TRUE
            INSTALL_RPATH "${ARMADILLO_LIBDIR}")
    endif(APPLE)
    target_link_libraries(${TEST} cfacc ${ARMADILLO_LIBRARIES})
endforeach()
foreach(TEST ${TESTS})
    add_test(NAME ${TEST} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${TEST})
endforeach()

