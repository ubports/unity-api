include_directories(${GLIB_INCLUDE_DIRS})

add_executable(GlibMemory_test
    GlibMemory_test.cpp
    )

target_link_libraries(GlibMemory_test
    ${TESTLIBS}
    ${GLIB_LDFLAGS}
    )

add_test(GlibMemory_test GlibMemory_test)
