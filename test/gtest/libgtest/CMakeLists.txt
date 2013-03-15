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

if (NOT DEFINED GTEST_SRC_DIR)
    set(GTEST_SRC_DIR /usr/src/gtest)
endif()

include(ExternalProject)

ExternalProject_Add(gtest
    SOURCE_DIR ${GTEST_SRC_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    INSTALL_COMMAND ""
)
