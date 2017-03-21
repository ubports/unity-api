add_subdirectory(internal)

set(UTIL_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Daemon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FileIO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IniParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SnapPath.cpp
)

set(UNITY_API_LIB_SRC ${UNITY_API_LIB_SRC} ${UTIL_SRC} PARENT_SCOPE)
