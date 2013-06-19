add_subdirectory(unity)

# Pseudo-library of object files. We need a dynamic version of the library for normal clients,
# and a static version for the whitebox tests, so we can write unit tests for classes in the internal namespaces
# (because, for the .so, non-public APIs are compiled with -fvisibility=hidden).
# Everything is compiled with -fPIC, so the same object files are suitable for either library.
# Here, we create an object library that then is used to link the static and dynamic
# libraries, without having to compile each source file twice with different compile flags.

set(UNITY_API_LIB_OBJ ${UNITY_API_LIB}-obj)
add_library(${UNITY_API_LIB_OBJ} OBJECT ${UNITY_API_LIB_SRC})
set_target_properties(${UNITY_API_LIB_OBJ} PROPERTIES COMPILE_FLAGS "-fPIC")
add_pch(pch/unityapi_pch.hh ${UNITY_API_LIB_OBJ})

# Use the object files to make the shared library.
set(UNITY_API_SOVERSION 0)
add_library(${UNITY_API_LIB} SHARED $<TARGET_OBJECTS:${UNITY_API_LIB_OBJ}>)
set_target_properties(${UNITY_API_LIB} PROPERTIES
    VERSION "${UNITY_API_MAJOR}.${UNITY_API_MINOR}"
    SOVERSION ${UNITY_API_SOVERSION}
)

# Use the object files to make the static library. We add -fPIC to avoid compiling a second time.
add_library(${UNITY_API_STATIC_LIB} STATIC $<TARGET_OBJECTS:${UNITY_API_LIB_OBJ}>)
set_target_properties(${UNITY_API_STATIC_LIB} PROPERTIES OUTPUT_NAME ${UNITY_API_LIB})

# Only the dynamic library gets installed.
install(TARGETS ${UNITY_API_LIB} LIBRARY DESTINATION ${LIB_INSTALL_PREFIX})

# Set up package config.
configure_file(lib${UNITY_API_LIB}.pc.in lib${UNITY_API_LIB}.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${UNITY_API_LIB}.pc DESTINATION ${LIB_INSTALL_PREFIX}/pkgconfig)

# Parent needs to know what all the source files are, for generating doc and the like.
set(UNITY_API_LIB_SRC ${UNITY_API_LIB_SRC} ${UNITY_SRC} PARENT_SCOPE)
