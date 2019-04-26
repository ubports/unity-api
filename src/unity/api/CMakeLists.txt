add_subdirectory(internal)

set(API_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Version.cpp
)

set(UNITY_API_LIB_SRC ${UNITY_API_LIB_SRC} ${API_SRC} PARENT_SCOPE)
