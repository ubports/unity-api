find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)

set(CMAKE_AUTOMOC ON)
add_definitions(-DQT_NO_KEYWORDS)

set(TestUtilQML_SOURCES
    testutil.cpp
    testutil_plugin.cpp
)

add_library(TestUtilQml MODULE ${TestUtilQML_SOURCES})

qt5_use_modules(TestUtilQml Core Quick)

# copy qmldir file into build directory for shadow builds
file(GLOB QML_JS_FILES *.js *.qml)

file(COPY qmldir ${QML_JS_FILES}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
