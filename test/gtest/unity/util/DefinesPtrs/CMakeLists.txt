add_executable(DefinesPtrs_test DefinesPtrs_test.cpp)
target_link_libraries(DefinesPtrs_test ${LIBS} ${TESTLIBS})

add_test(DefinesPtrs DefinesPtrs_test)
