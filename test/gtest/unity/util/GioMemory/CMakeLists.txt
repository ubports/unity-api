pkg_check_modules(GIO REQUIRED gio-2.0)
pkg_check_modules(QDBUSTEST REQUIRED libqtdbustest-1)

find_package(Qt5Core REQUIRED)
find_package(Qt5DBus REQUIRED)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5DBus_INCLUDE_DIRS}
    ${GIO_INCLUDE_DIRS}
    ${QDBUSTEST_INCLUDE_DIRS}
    )

add_definitions(
    -DQT_NO_KEYWORDS=1
    )

add_executable(GioMemory_test
    GioMemory_test.cpp
    )

target_link_libraries(GioMemory_test
    ${TESTLIBS}
    ${GIO_LDFLAGS}
    ${QDBUSTEST_LDFLAGS}
    Qt5::Core
    Qt5::DBus
    )

add_test(GioMemory_test GioMemory_test)
