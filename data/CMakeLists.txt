# Set up package config.
set(PKGCONFIG_NAME "unity-shell-api")
set(PKGCONFIG_DESCRIPTION "Unity shell APIs")
set(PKGCONFIG_PLUGINDIR "${SHELL_PLUGINDIR}")
set(VERSION "1.0")

configure_file(unity-shell-api.pc.in unity-shell-api.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/unity-shell-api.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

configure_file(lib${UNITY_API_LIB}.pc.in lib${UNITY_API_LIB}.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${UNITY_API_LIB}.pc DESTINATION ${LIB_INSTALL_PREFIX}/pkgconfig)

