include_directories(
    ${CMAKE_SOURCE_DIR}/include/unity/shell/application
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Qml REQUIRED)

set(ApplicationMocks_SOURCES
    ${CMAKE_SOURCE_DIR}/include/unity/shell/application/ApplicationManagerInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/application/ApplicationInfoInterface.h
    Mocks/MockApplicationManager.cpp
    Mocks/MockApplicationInfo.cpp
)

add_library(ApplicationMocks SHARED ${ApplicationMocks_SOURCES})

target_link_libraries(ApplicationMocks Qt5::Core Qt5::Gui)

set(TestApplicationPlugin_SOURCES
    TestApplicationPlugin.cpp
)

add_library(TestApplicationPlugin MODULE ${TestApplicationPlugin_SOURCES})

target_link_libraries(TestApplicationPlugin Qt5::Core Qt5::Gui Qt5::Quick)

target_link_libraries(TestApplicationPlugin ApplicationMocks)

add_custom_target(TestApplicationPluginQmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS qmldir
)
