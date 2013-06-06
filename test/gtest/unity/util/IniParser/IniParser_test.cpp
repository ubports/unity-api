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

TEST(IniParser, has) {
    IniParser conf(INI_FILE);

    ASSERT_TRUE(conf.hasGroup("first"));
    ASSERT_FALSE(conf.hasGroup("nonexisting"));

    ASSERT_TRUE(conf.hasKey("first", "stringvalue"));
    ASSERT_FALSE(conf.hasKey("first", "missingvalue"));
}

TEST(IniParser, simpleQueries) {
    IniParser conf(INI_FILE);
    vector<string> groups = conf.getGroups();

    ASSERT_EQ(conf.getStartGroup(), "first");

    ASSERT_EQ(groups.size(), 2);
    ASSERT_EQ(groups[0], "first");
    ASSERT_EQ(groups[1], "second");

    vector<string> firstKeys = conf.getKeys("first");
    ASSERT_EQ(firstKeys.size(), 5);
    ASSERT_EQ(firstKeys[1], "boolvalue");

    ASSERT_EQ(conf.getString("first", "stringvalue"), "hello");
    ASSERT_EQ(conf.getInt("first", "intvalue"), 1);
    ASSERT_FALSE(conf.getBoolean("second", "boolvalue"));
}

TEST(IniParser, arrayQueries) {
    IniParser conf(INI_FILE);
    vector<string> strArr = conf.getStringArray("first", "array");

    ASSERT_EQ(strArr.size(), 3);
    ASSERT_EQ(strArr[0], "foo");
    ASSERT_EQ(strArr[1], "bar");
    ASSERT_EQ(strArr[2], "baz");

    vector<int> intArr = conf.getIntArray("second", "intarray");
    ASSERT_EQ(intArr.size(), 9);
    ASSERT_EQ(intArr[0], 4);
    ASSERT_EQ(intArr[8], 3);

    vector<bool> boolArr = conf.getBooleanArray("first", "boolarray");
    ASSERT_EQ(boolArr.size(), 3);
    ASSERT_TRUE(boolArr[0]);
    ASSERT_FALSE(boolArr[1]);
    ASSERT_FALSE(boolArr[2]);
}

TEST(IniParser, failingQueries) {
    IniParser conf(INI_FILE);

    try {
        conf.getString("foo", "bar");
        FAIL();
    } catch(const InvalidArgumentException &e) {
    }
    try {
        conf.getInt("foo", "bar");
        FAIL();
    } catch(const InvalidArgumentException &e) {
    }
    try {
        conf.getBoolean("foo", "bar");
        FAIL();
    } catch(const InvalidArgumentException &e) {
    }

    try {
        conf.getIntArray("first", "array");
        FAIL();
    } catch(const InvalidArgumentException &e) {
    }

    try {
        conf.getBooleanArray("first", "array");
        FAIL();
    } catch(const InvalidArgumentException &e) {
    }
}
