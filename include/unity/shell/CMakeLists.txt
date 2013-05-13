add_subdirectory(notifications)

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB internal_headers "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.h")

install(FILES ${headers} DESTINATION ${HDR_INSTALL_DIR}/unity/shell)

set(UNITY_API_LIB_HDRS ${UNITY_API_LIB_HDRS} ${headers} ${internal_headers} PARENT_SCOPE)
