#
# Copyright (C) 2013 Canonical Ltd
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>
#

if (CMAKE_BUILD_TYPE MATCHES coverage)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --coverage")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")

  find_program(GCOVR_EXECUTABLE gcovr HINTS ${GCOVR_ROOT} "${GCOVR_ROOT}/bin")
  if (NOT GCOVR_EXECUTABLE)
    message(STATUS "Gcovr binary was not found, cannot generate XML coverage info.")
  else ()
    message(STATUS "Gcovr found, can generate XML coverage info.")
    add_custom_target (coverage-xml
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMAND "${GCOVR_EXECUTABLE}" --exclude="test_.cpp*" -x -r "${CMAKE_SOURCE_DIR}"
      --object-directory=${CMAKE_BINARY_DIR} -o coverage.xml)
  endif()

  find_program(LCOV_EXECUTABLE lcov HINTS ${LCOV_ROOT} "${GCOVR_ROOT}/bin")
  find_program(GENHTML_EXECUTABLE genhtml HINTS ${GENHTML_ROOT})
  if (NOT LCOV_EXECUTABLE)
    message(STATUS "Lcov binary was not found, cannot generate HTML coverage info.")
  else ()
    if(NOT GENHTML_EXECUTABLE)
      message(STATUS "Genthml binary not found, cannot generate HTML coverage info.")
    else()
      message(STATUS "Lcov and genhtml found, can generate HTML coverage info.")
      add_custom_target (coverage-html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND "${LCOV_EXECUTABLE}" --directory ${CMAKE_BINARY_DIR} --quiet --no-compat-libtool
            --capture --output-file coverage.info --no-checksum
        COMMAND "${LCOV_EXECUTABLE}" --directory ${CMAKE_BINARY_DIR} --quiet
            --remove coverage.info 'test/*' -o coverage.info
        COMMAND "${LCOV_EXECUTABLE}" --directory ${CMAKE_BINARY_DIR} --quiet
            --remove coverage.info '/usr/include/*' -o coverage.info
        COMMAND "${GENHTML_EXECUTABLE}" --prefix ${CMAKE_BINARY_DIR} --output-directory coveragereport
            --title "Code Coverage" --legend --show-details coverage.info
      )
    endif()
  endif()
endif()
