add_subdirectory(api)
add_subdirectory(scopes)
add_subdirectory(util)

add_executable(Exceptions_test Exceptions_test.cpp)
target_link_libraries(Exceptions_test ${LIBS} ${TESTLIBS})

add_test(Exceptions Exceptions_test)
