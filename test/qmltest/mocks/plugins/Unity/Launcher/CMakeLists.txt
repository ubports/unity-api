include_directories(
    ${CMAKE_SOURCE_DIR}/include/unity/shell/launcher
    ${CMAKE_SOURCE_DIR}/include/unity/shell/application
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../Application/
)

add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Qml REQUIRED)

set(LauncherMocks_SOURCES
    ${CMAKE_SOURCE_DIR}/include/unity/shell/launcher/LauncherModelInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/launcher/LauncherItemInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/launcher/QuickListModelInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/launcher/AppDrawerModelInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/application/ApplicationManagerInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/application/ApplicationInfoInterface.h
    Mocks/MockLauncherModel.cpp
    Mocks/MockLauncherItem.cpp
    Mocks/MockQuickListModel.cpp
    Mocks/MockAppDrawerModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Application/Mocks/MockApplicationManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Application/Mocks/MockApplicationInfo.cpp
)

add_library(LauncherMocks SHARED ${LauncherMocks_SOURCES})

#find_package(Qt5Gui REQUIRED)
target_link_libraries(LauncherMocks Qt5::Core Qt5::Gui)

set(TestLauncherPlugin_SOURCES
    TestLauncherPlugin.cpp
)

add_library(TestLauncherPlugin MODULE ${TestLauncherPlugin_SOURCES})

target_link_libraries(TestLauncherPlugin Qt5::Core Qt5::Quick)

target_link_libraries(TestLauncherPlugin LauncherMocks)

add_custom_target(TestLauncherPluginQmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS qmldir
)
