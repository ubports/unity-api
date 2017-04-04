add_executable(SnapPath_test SnapPath_test.cpp)
target_link_libraries(SnapPath_test ${LIBS} ${TESTLIBS})

add_test(SnapPath SnapPath_test)
