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
# Authored by: Michi Henning <michi.henning@canonical.com>
#

cmake_minimum_required(VERSION 2.8.10)

#
# Default install location. Must be set here, before setting the project.
#
if (NOT DEFINED CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "" FORCE)
endif()

#
# Project
#

project(unity-api)
set(PROJECT_NAME "unity-api")

#
# Version
#

set(UNITY_API_MAJOR 0)
set(UNITY_API_MINOR 1)
set(UNITY_API_MICRO 0)
set(UNITY_API_VERSION "${UNITY_API_MAJOR}.${UNITY_API_MINOR}.${UNITY_API_MICRO}")

#
# Compiler flags
#

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-permissive -pedantic -Wall -Wextra")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "relwithdebinfo")
    option(Werror "Treat warnings as errors" ON)
else()
    option(Werror "Treat warnings as errors" OFF)
endif()

if (Werror)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

#
# Packages we depend on. TODO: Lots of prerequisites need to be added here, but there doesn't appear
# to be a Find<name> module for most of them.
#

find_package(Boost 1.49.0 COMPONENTS regex REQUIRED)

#
# Names of the libraries we create and link against.
#

set(UNITY_API_LIB unity-api)
set(OTHER_LIBS )

#
# All the libraries we need to link a normal executable.
#

set(LIBS ${UNITY_API_LIB} ${OTHER_LIBS})

#
# Definitions for testing with valgrind.
#

find_program(MEMORYCHECK_COMMAND NAMES valgrind)
if (MEMORYCHECK_COMMAND)
    set(MEMORYCHECK_COMMAND_OPTIONS
        "--suppressions=${CMAKE_SOURCE_DIR}/valgrind-suppress --leak-check=full
        --num-callers=40 --error-exitcode=3"
  )
endif()

add_custom_target(valgrind DEPENDS NightlyMemCheck)

#
# Definitions for coverage testing
#

include(cmake/coverage.cmake)

# This gets rid of any stale .gcda files. Run this if a running a binary causes lots of messages about
# about a "merge mismatch for summaries".

add_custom_target(clean-coverage
        COMMAND find ${CMAKE_BINARY_DIR} -name '*.gcda' | xargs rm -f
)

add_custom_target(cppcheck COMMAND cppcheck --enable=all -q --error-exitcode=2
                      ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/test)

#
# Enable tests
#

include(CTest)
enable_testing()

#
# Documentation
#

find_package(Doxygen)
if (NOT DOXYGEN_FOUND)
    message(Warning "Cannot generate documentation: doxygen not found")
else()
  configure_file(${PROJECT_SOURCE_DIR}/doc/Doxyfile.in ${PROJECT_BINARY_DIR}/doc/Doxyfile @ONLY IMMEDIATE)
  add_custom_target(doc
      COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/doc/Doxyfile
      SOURCES ${PROJECT_BINARY_DIR}/doc/Doxyfile)
endif()

#
# Directories
#

include_directories(
    include
    ${CMAKE_BINARY_DIR}/include
    ${Boost_INCLUDE_DIR}
)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)

#
# Used by some of the test scripts to filter out files that are generated as part of a build. Build directories (for
# in-tree builds) are expected to include this string in their name, for example, "build-debug" or "debug-build".
#
set(BUILD_DIR_NAME build)
