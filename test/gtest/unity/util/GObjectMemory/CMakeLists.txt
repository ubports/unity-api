pkg_check_modules(GOBJECT REQUIRED gobject-2.0)

include_directories(${GOBJECT_INCLUDE_DIRS})

add_executable(GObjectMemory_test
    GObjectMemory_test.cpp
    )

target_link_libraries(GObjectMemory_test
    ${TESTLIBS}
    ${GOBJECT_LDFLAGS}
    )

add_test(GObjectMemory_test GObjectMemory_test)
