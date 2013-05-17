include(QmlTest)

set(qmltest_DEFAULT_IMPORT_PATHS
  ${CMAKE_BINARY_DIR}/test/qmltest/modules
  ${CMAKE_BINARY_DIR}/test/qmltest/mocks/plugins
)
set(qmltest_DEFAULT_PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=minimal")

add_qml_test(notifications Notifications)
