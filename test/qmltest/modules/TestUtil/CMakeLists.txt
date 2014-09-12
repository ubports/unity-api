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
add_custom_target(TestUtil-qmlfiles ALL
                    COMMAND cp qmldir ${QML_JS_FILES} ${CMAKE_CURRENT_BINARY_DIR}
                    DEPENDS ${QML_JS_FILES}
                    SOURCES ${QML_JS_FILES}
)

# tests
include(QmlTest)

add_qml_test(test TestUtil
    IMPORT_PATHS ${CMAKE_BINARY_DIR}/test/qmltest/modules
    PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=minimal"
)
