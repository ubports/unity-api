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

find_package(Threads)
if(NOT Threads_FOUND)
  message(FATAL_ERROR "Thread library not found.")
endif()
set(TESTLIBDIR ${CMAKE_BINARY_DIR}/test/gtest/libgtest/build)
set(LIBGTEST ${TESTLIBDIR}/libgtest_main.a ${TESTLIBDIR}/libgtest.a)
set(TESTLIBS ${LIBGTEST} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(libgtest)
add_subdirectory(unity)

set(TEST_SRC
)

foreach(src ${TEST_SRC})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
    target_link_libraries(${name} ${LIBS} ${TESTLIBS})
    string(REPLACE "_test" "" test_name ${name})
    add_test(${test_name} ${name})
endforeach(src)
