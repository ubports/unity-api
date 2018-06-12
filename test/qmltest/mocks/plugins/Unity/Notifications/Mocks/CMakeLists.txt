set(MockNotificationsPlugin_SOURCES
    MockNotificationsPlugin.cpp
)

add_library(MockNotificationsPlugin MODULE ${MockNotificationsPlugin_SOURCES})

#find_package(Qt5Core REQUIRED)
#find_package(Qt5Quick REQUIRED)
target_link_libraries(MockNotificationsPlugin Qt5::Core Qt5::Quick)

target_link_libraries(MockNotificationsPlugin NotificationsMocks)

add_custom_target(MockNotificationsPluginQmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS qmldir
)
