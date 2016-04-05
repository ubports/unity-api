add_executable(IniParser_test IniParser_test.cpp)
target_link_libraries(IniParser_test ${LIBS} ${TESTLIBS})

add_definitions(-DTEST_RUNTIME_PATH="${CMAKE_CURRENT_BINARY_DIR}")

add_test(IniParser IniParser_test)
