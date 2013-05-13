include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)

set(Mocks_SOURCES
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/enums.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/model.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/source.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/notifications/notification.h
    Mocks/mockmodel.cpp
    Mocks/mocksource.cpp
    Mocks/mocknotification.cpp
    Mocks/mockactionmodel.cpp
)

add_library(Mocks SHARED ${Mocks_SOURCES})

qt5_use_modules(Mocks Core)

set(Notifications_SOURCES
    testnotificationsplugin.cpp
)

add_library(Notifications MODULE ${Notifications_SOURCES})

qt5_use_modules(Notifications Core Quick)

target_link_libraries(Notifications Mocks)

add_custom_target(NotificationsQmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS qmldir
)

add_subdirectory(Mocks)
