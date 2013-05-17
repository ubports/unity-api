find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)

set(CMAKE_AUTOMOC ON)
add_definitions(-DQT_NO_KEYWORDS)

set(TestUtilQML_SOURCES
    TestUtil.cpp
    TestUtilPlugin.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(TestUtilQml MODULE ${TestUtilQML_SOURCES})

qt5_use_modules(TestUtilQml Core Quick)

# copy qmldir file into build directory for shadow builds
file(GLOB QML_JS_FILES *.js *.qml)

file(COPY qmldir ${QML_JS_FILES}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )


# tests
include(QmlTest)

add_qml_test(test TestUtil
    IMPORT_PATHS ${CMAKE_BINARY_DIR}/test/qmltest/modules
    PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=minimal"
)
