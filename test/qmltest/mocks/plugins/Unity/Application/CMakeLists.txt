include_directories(
    ${CMAKE_SOURCE_DIR}/include/unity/shell/application
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Qml REQUIRED)

set(ApplicationMocks_SOURCES
    ${CMAKE_SOURCE_DIR}/include/unity/shell/application/ApplicationManagerInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/application/ApplicationInfoInterface.h
    Mocks/MockApplicationManager.cpp
    Mocks/MockApplicationInfo.cpp
)

add_library(ApplicationMocks SHARED ${ApplicationMocks_SOURCES})

qt5_use_modules(ApplicationMocks Core)

set(TestApplicationPlugin_SOURCES
    TestApplicationPlugin.cpp
)

add_library(TestApplicationPlugin MODULE ${TestApplicationPlugin_SOURCES})

qt5_use_modules(TestApplicationPlugin Core Quick)

target_link_libraries(TestApplicationPlugin ApplicationMocks)

add_custom_target(TestApplicationPluginQmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS qmldir
)
