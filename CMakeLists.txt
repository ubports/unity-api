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

include(cmake/coverage.cmake)

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -fno-permissive -pedantic -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_DEBUG} "-g3")
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_RELEASE} "-g3 -Werror")

#
# Select debug or release mode.
#

add_custom_target(debug-build
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=debug ${PROJECT_SOURCE_DIR}
)

add_custom_target(release-build
    ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=release ${PROJECT_SOURCE_DIR}
)

add_custom_target(coverage-build
    ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=coverage ${PROJECT_SOURCE_DIR}
)

#
# Packages we depend on. TODO: Lots of prerequisites need to be added here, but there doesn't appear
# to be a Find<name> module for most of them.
#

#find_package(whatever)

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
# Location where gtest source is installed.
#

set(GTEST_SRC_DIR /usr/src/gtest)

#
# Definitions for testing with valgrind.
#

find_program(MEMORYCHECK_COMMAND NAMES valgrind)
if(MEMORYCHECK_COMMAND)
    set(MEMORYCHECK_COMMAND_OPTIONS
        "--suppressions=${CMAKE_SOURCE_DIR}/valgrind-suppress --leak-check=full
        --num-callers=40 --error-exitcode=3"
  )
endif()

add_custom_target(valgrind COMMAND make NightlyMemCheck)

#
# Definitions for coverage testing
#

find_program(COVERAGE_COMMAND NAMES gcov)
if(COVERAGE_COMMAND)
    set(COVERAGE_COMMAND_OPTIONS "")
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "coverage")
    add_custom_target(coverage
        COMMAND ${CMAKE_SOURCE_DIR}/test/gcov/gcov.py -i ${CMAKE_SOURCE_DIR}/include
                    ${CMAKE_BINARY_DIR}/Testing/CoverageInfo ${CMAKE_SOURCE_DIR}/test/gcov/expected
        DEPENDS NightlyCoverage
    )
else()
    add_custom_target(coverage
        COMMAND echo "Coverage testing is available only for coverage builds" >&2
        COMMAND false
    )
endif()

# This gets rid of any stale .gcda files. Run this if a running a binary causes lots of messages about
# about a "merge mismatch for summaries".

add_custom_target(clean-coverage
        COMMAND find ${CMAKE_BINARY_DIR} -name '*.gcda' | xargs rm -f
)

set(lcov_dir ${CMAKE_BINARY_DIR}/lcov)

file(MAKE_DIRECTORY ${lcov_dir})

if("${CMAKE_BUILD_TYPE}" STREQUAL "coverage")
    add_custom_target(lcov
        COMMAND lcov --quiet --no-compat-libtool --capture --directory ${CMAKE_BINARY_DIR} --output-file ${lcov_dir}/coverage.info
        COMMAND lcov --quiet --remove ${lcov_dir}/coverage.info 'test/*' -o ${lcov_dir}/coverage.info
        COMMAND lcov --quiet --remove ${lcov_dir}/coverage.info 'boost/*' -o ${lcov_dir}/coverage.info
        COMMAND lcov --quiet --remove ${lcov_dir}/coverage.info '/usr/include/*' -o ${lcov_dir}/coverage.info
        COMMAND genhtml ${lcov_dir}/coverage.info --output-directory ${lcov_dir} --demangle-cpp)
else()
    add_custom_target(lcov
        COMMAND echo "Coverage testing is available only for coverage builds" >&2
        COMMAND false
    )
endif()

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
    message(FATAL_ERROR "Cannot generate documentation: doxygen not found")
endif()

configure_file(${PROJECT_SOURCE_DIR}/doc/Doxyfile.in ${PROJECT_BINARY_DIR}/doc/Doxyfile @ONLY IMMEDIATE)

add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/doc/Doxyfile
    SOURCES ${PROJECT_BINARY_DIR}/doc/Doxyfile)

#
# Directories
#

include_directories(
    include
    ${CMAKE_BINARY_DIR}/include
)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)

#
# Used by some of the test scripts to filter out files that are generated as part of a build. Build directories (for
# in-tree builds) are expected to include this string in their name, for example, "build-debug" or "debug-build".
#
set(BUILD_DIR_NAME build)
