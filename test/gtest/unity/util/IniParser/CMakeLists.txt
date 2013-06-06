add_executable(IniParser_test IniParser_test.cpp)
target_link_libraries(IniParser_test ${LIBS} ${TESTLIBS})

add_test(IniParser IniParser_test)
