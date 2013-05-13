add_executable(FileIO_test FileIO_test.cpp)
target_link_libraries(FileIO_test ${LIBS} ${TESTLIBS})

add_test(FileIO FileIO_test)
