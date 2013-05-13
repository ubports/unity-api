find_package(Threads REQUIRED)
set(TESTLIBDIR ${CMAKE_BINARY_DIR}/test/gtest/libgtest/build)
set(LIBGTEST gtest)
set(TESTLIBS ${LIBGTEST} ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(libgtest)
add_subdirectory(unity)

set(TEST_SRC
)

foreach(src ${TEST_SRC})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
    target_link_libraries(${name} ${LIBS} ${TESTLIBS})
    string(REPLACE "_test" "" test_name ${name})
    add_test(${test_name} ${name})
endforeach(src)
