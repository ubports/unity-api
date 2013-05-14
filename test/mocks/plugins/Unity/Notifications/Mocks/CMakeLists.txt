set(MockNotificationsPlugin_SOURCES
    MockNotificationsPlugin.cpp
)

add_library(MockNotificationsPlugin MODULE ${MockNotificationsPlugin_SOURCES})

qt5_use_modules(MockNotificationsPlugin Core Quick)

target_link_libraries(MockNotificationsPlugin NotificationsMocks)

add_custom_target(MockNotificationsPluginQmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS qmldir
)
