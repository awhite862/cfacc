set(SRC
    cfrac.C
)

add_library(cfacc ${SRC})
include_directories(${CFACC_DIR})

if(OPENMP_FOUND)
    set_target_properties(cfacc PROPERTIES COMPILE_FLAGS "${OpenMP_CXX_FLAGS}")
else(OPENMP_FOUND)
    #    set_target_properties(cfacc PROPERTIES COMPILE_FLAGS)
endif(OPENMP_FOUND)

install(TARGETS cfacc DESTINATION lib)
