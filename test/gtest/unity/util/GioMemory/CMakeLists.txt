pkg_check_modules(GIO REQUIRED gio-2.0)

include_directories(${GIO_INCLUDE_DIRS})

add_executable(GioMemory_test
    GioMemory_test.cpp
    )

target_link_libraries(GioMemory_test
    ${TESTLIBS}
    ${GIO_LDFLAGS}
    )

add_test(GioMemory_test GioMemory_test)
