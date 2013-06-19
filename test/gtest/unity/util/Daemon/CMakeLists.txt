add_executable(Daemon_test Daemon_test.cpp)
target_link_libraries(Daemon_test ${TESTLIBS})

add_test(Daemon ${CMAKE_CURRENT_SOURCE_DIR}/daemon-tester.py ${CMAKE_CURRENT_BINARY_DIR}/Daemon_test)
