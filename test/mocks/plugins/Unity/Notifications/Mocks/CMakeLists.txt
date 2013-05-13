set(NotificationsMocks_SOURCES
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/model.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/source.h
    mocknotificationsplugin.cpp
)

add_library(NotificationsMocks MODULE ${NotificationsMocks_SOURCES})

qt5_use_modules(NotificationsMocks Core Quick)

target_link_libraries(NotificationsMocks Mocks)

add_custom_target(NotificationsMocksQmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS qmldir
)
