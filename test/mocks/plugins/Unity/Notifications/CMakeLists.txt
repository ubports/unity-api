include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)

set(NotificationsMocks_SOURCES
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/Enums.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/ModelInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/SourceInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/NotificationInterface.h
    Mocks/MockModel.cpp
    Mocks/MockSource.cpp
    Mocks/MockNotification.cpp
    Mocks/MockActionModel.cpp
)

add_library(NotificationsMocks SHARED ${NotificationsMocks_SOURCES})

qt5_use_modules(NotificationsMocks Core)

set(TestNotificationsPlugin_SOURCES
    TestNotificationsPlugin.cpp
)

add_library(TestNotificationsPlugin MODULE ${TestNotificationsPlugin_SOURCES})

qt5_use_modules(TestNotificationsPlugin Core Quick)

target_link_libraries(TestNotificationsPlugin NotificationsMocks)

add_custom_target(TestNotificationsPluginQmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS qmldir
)

add_subdirectory(Mocks)
