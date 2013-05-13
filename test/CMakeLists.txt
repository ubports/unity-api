add_subdirectory(gtest)
add_subdirectory(cleanincludes)
add_subdirectory(headers)
add_subdirectory(copyright)
add_subdirectory(whitespace)


include(QmlTest)
add_subdirectory(mocks)

set(qmltest_DEFAULT_IMPORT_PATHS
  ${CMAKE_BINARY_DIR}/src/modules
  ${CMAKE_BINARY_DIR}/test/mocks/plugins
)
set(qmltest_DEFAULT_PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=minimal")

add_qml_test(modules/TestUtil TestUtil)

add_qml_test(unity/shell/notifications Notifications)
