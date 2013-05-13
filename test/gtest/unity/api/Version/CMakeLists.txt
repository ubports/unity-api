add_executable(Version_test Version_test.cpp)
target_link_libraries(Version_test ${LIBS} ${TESTLIBS})

add_test(Version Version_test)
