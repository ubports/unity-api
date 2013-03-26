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

add_executable(Daemon_test Daemon_test.cpp)
target_link_libraries(Daemon_test ${LIBS} ${TESTLIBS})

add_test(Daemon ${CMAKE_CURRENT_SOURCE_DIR}/daemon-tester.py ${CMAKE_CURRENT_BINARY_DIR}/Daemon_test)
