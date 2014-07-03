set(INCLUDE_INSTALL_DIR include/unity/shell/scopes)

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB internal_headers "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.h")

install(FILES ${headers} DESTINATION ${INCLUDE_INSTALL_DIR})

set(UNITY_API_LIB_HDRS ${UNITY_API_LIB_HDRS} ${headers} ${internal_headers} PARENT_SCOPE)

set(VERSION 2)
set(PKGCONFIG_NAME "unity-shell-scopes")
set(PKGCONFIG_DESCRIPTION "Unity shell Scopes APIs")
set(PKGCONFIG_REQUIRES "Qt5Core")
set(PKGCONFIG_FILE unity-shell-scopes.pc)

configure_file(${CMAKE_SOURCE_DIR}/data/unity-shell-api.pc.in
  ${CMAKE_BINARY_DIR}/data/${PKGCONFIG_FILE} @ONLY
)

install(FILES ${CMAKE_BINARY_DIR}/data/${PKGCONFIG_FILE}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
