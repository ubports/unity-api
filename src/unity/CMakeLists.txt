add_subdirectory(api)
add_subdirectory(internal)
add_subdirectory(util)

set(UNITY_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Exception.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UnityExceptions.cpp
)

set(UNITY_API_LIB_SRC ${UNITY_API_LIB_SRC} ${UNITY_SRC} PARENT_SCOPE)
