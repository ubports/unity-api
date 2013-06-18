add_executable(ResourcePtr_test ResourcePtr_test.cpp)
target_link_libraries(ResourcePtr_test ${TESTLIBS})

add_test(ResourcePtr ResourcePtr_test)
