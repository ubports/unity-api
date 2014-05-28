include_directories(
    ${CMAKE_SOURCE_DIR}/include/unity/shell/scopes
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Qml REQUIRED)

set(ScopesMocks_SOURCES
    Mocks/MockCategories.cpp
    Mocks/MockResultsModel.cpp
    Mocks/MockPreviewModel.cpp
    Mocks/MockPreviewStack.cpp
    Mocks/MockPreviewWidgetModel.cpp
    Mocks/MockScope.cpp
    Mocks/MockScopes.cpp
    ${CMAKE_SOURCE_DIR}/include/unity/shell/scopes/CategoriesInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/scopes/DepartmentInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/scopes/ResultsModelInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/scopes/PreviewModelInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/scopes/PreviewWidgetModelInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/scopes/PreviewStackInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/scopes/ScopeInterface.h
    ${CMAKE_SOURCE_DIR}/include/unity/shell/scopes/ScopesInterface.h
)

add_library(ScopesMocks SHARED ${ScopesMocks_SOURCES})

qt5_use_modules(ScopesMocks Core)

set(TestScopesPlugin_SOURCES
    TestScopesPlugin.cpp
)

add_library(TestScopesPlugin MODULE ${TestScopesPlugin_SOURCES})

qt5_use_modules(TestScopesPlugin Core Quick)

target_link_libraries(TestScopesPlugin ScopesMocks)

add_custom_target(TestScopesPluginQmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS qmldir
)
