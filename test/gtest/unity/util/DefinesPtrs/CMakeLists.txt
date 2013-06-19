add_executable(DefinesPtrs_test DefinesPtrs_test.cpp)
target_link_libraries(DefinesPtrs_test ${TESTLIBS})

add_test(DefinesPtrs DefinesPtrs_test)
