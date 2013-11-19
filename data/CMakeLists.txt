# Set up package config.
set(PKGCONFIG_NAME "unity-shell-api")
set(PKGCONFIG_DESCRIPTION "Unity shell APIs")
set(PKGCONFIG_PLUGINDIR "${SHELL_PLUGINDIR}")
set(VERSION "1.0")

configure_file(unity-shell-api.pc.in unity-shell-api.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/unity-shell-api.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
