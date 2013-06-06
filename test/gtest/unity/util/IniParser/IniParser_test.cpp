/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>
 */

#include <gtest/gtest.h>
#include <unity/UnityExceptions.h>
#include <unity/util/IniParser.h>
#include <unity-api-test-config.h>

using namespace std;
using namespace unity;
using namespace unity::util;

#define INI_FILE UNITY_API_TEST_DATADIR "/sample.ini"

TEST(IniParser, basic) {
    IniParser test(INI_FILE);
}

TEST(IniParser, missingFile) {
    try {
        IniParser("nonexistant");
        FAIL();
    } catch(const InvalidArgumentException &e) {
    }
}
