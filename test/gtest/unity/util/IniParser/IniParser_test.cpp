/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
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
#define INI_TEMP_FILE TEST_RUNTIME_PATH "/temp.ini"

TEST(IniParser, basic)
{
    IniParser test(INI_FILE);
}

TEST(IniParser, missingFile)
{
    try {
        IniParser("nonexistant");
        FAIL();
    } catch(const FileException &e) {
    }
}

TEST(IniParser, has)
{
    IniParser conf(INI_FILE);

    ASSERT_TRUE(conf.has_group("first"));
    ASSERT_FALSE(conf.has_group("nonexisting"));

    ASSERT_TRUE(conf.has_key("first", "stringvalue"));
    ASSERT_FALSE(conf.has_key("first", "missingvalue"));
}

TEST(IniParser, simpleQueries)
{
    IniParser conf(INI_FILE);
    vector<string> groups = conf.get_groups();

    ASSERT_EQ("first", conf.get_start_group());

    ASSERT_EQ(2, groups.size());
    ASSERT_EQ("first", groups[0]);
    ASSERT_EQ("second", groups[1]);

    vector<string> firstKeys = conf.get_keys("first");
    ASSERT_EQ(10, firstKeys.size());
    ASSERT_EQ("boolvalue", firstKeys[1]);

    ASSERT_EQ(conf.get_string("first", "stringvalue"), "hello");
    ASSERT_EQ(1, conf.get_int("first", "intvalue"));
    ASSERT_FALSE(conf.get_boolean("second", "boolvalue"));

    ASSERT_EQ("world", conf.get_string("first", "locstring"));
    ASSERT_EQ("world", conf.get_locale_string("first", "locstring", "en"));
    ASSERT_EQ("mundo", conf.get_locale_string("first", "locstring", "pt_BR"));
    ASSERT_EQ("world", conf.get_locale_string("first", "locstring", "no_DF"));
}

TEST(IniParser, arrayQueries)
{
    IniParser conf(INI_FILE);
    vector<string> strArr = conf.get_string_array("first", "array");

    ASSERT_EQ(3, strArr.size());
    ASSERT_EQ("foo", strArr[0]);
    ASSERT_EQ("bar", strArr[1]);
    ASSERT_EQ("baz", strArr[2]);

    vector<int> intArr = conf.get_int_array("second", "intarray");
    ASSERT_EQ(9, intArr.size());
    ASSERT_EQ(4, intArr[0]);
    ASSERT_EQ(3, intArr[8]);

    vector<bool> boolArr = conf.get_boolean_array("first", "boolarray");
    ASSERT_EQ(3, boolArr.size());
    ASSERT_TRUE(boolArr[0]);
    ASSERT_FALSE(boolArr[1]);
    ASSERT_FALSE(boolArr[2]);

    strArr = conf.get_string_array("first", "stringarray");
    ASSERT_EQ(3, strArr.size());
    ASSERT_EQ("a", strArr[0]);
    ASSERT_EQ("b", strArr[1]);
    ASSERT_EQ("c", strArr[2]);

    strArr = conf.get_locale_string_array("first", "locstringarray", "pt_BR");
    ASSERT_EQ(3, strArr.size());
    ASSERT_EQ("x", strArr[0]);
    ASSERT_EQ("y", strArr[1]);
    ASSERT_EQ("z", strArr[2]);
}

TEST(IniParser, failingQueries)
{
    IniParser conf(INI_FILE);

    try {
        conf.get_string("foo", "bar");
        FAIL();
    } catch(const LogicException &e) {
    }
    try {
        conf.get_locale_string("foo", "bar");
        FAIL();
    } catch(const LogicException &e) {
    }
    try {
        conf.get_int("foo", "bar");
        FAIL();
    } catch(const LogicException &e) {
    }
    try {
        conf.get_boolean("foo", "bar");
        FAIL();
    } catch(const LogicException &e) {
    }

    try {
        conf.get_int_array("first", "array");
        FAIL();
    } catch(const LogicException &e) {
    }

    try {
        conf.get_boolean_array("first", "array");
        FAIL();
    } catch(const LogicException &e) {
    }
}

TEST(IniParser, write)
{
    // Create empty ini file for writing
    FILE* f = fopen(INI_TEMP_FILE, "w");
    fclose(f);

    IniParser conf(INI_TEMP_FILE);

    conf.set_boolean("hello", "there", true);
    conf.sync();
}
