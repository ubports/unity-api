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

    ASSERT_FALSE(conf.has_key("first", "missingvalue"));
    ASSERT_FALSE(conf.has_group("nonexisting"));

    ASSERT_TRUE(conf.has_key("first", "stringvalue"));
    ASSERT_TRUE(conf.has_group("first"));

    ASSERT_TRUE(conf.remove_key("first", "stringvalue"));
    EXPECT_THROW(conf.remove_key("first", "missingvalue"), LogicException);

    ASSERT_FALSE(conf.has_key("first", "stringvalue"));
    ASSERT_TRUE(conf.has_group("first"));

    ASSERT_TRUE(conf.remove_group("first"));
    EXPECT_THROW(conf.remove_group("nonexisting"), LogicException);

    EXPECT_THROW(conf.has_key("first", "stringvalue"), LogicException);
    ASSERT_FALSE(conf.has_group("first"));
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
    ASSERT_EQ(11, firstKeys.size());
    ASSERT_EQ("boolvalue", firstKeys[2]);

    ASSERT_EQ(conf.get_string("first", "stringvalue"), "hello");
    ASSERT_EQ(1, conf.get_int("first", "intvalue"));
    ASSERT_EQ(1, conf.get_double("first", "intvalue"));
    ASSERT_EQ(2.345, conf.get_double("first", "doublevalue"));
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

    vector<double> intToDblArr = conf.get_double_array("second", "intarray");
    ASSERT_EQ(9, intToDblArr.size());
    ASSERT_EQ(4, intToDblArr[0]);
    ASSERT_EQ(3, intToDblArr[8]);

    vector<double> dblArr = conf.get_double_array("second", "doublearray");
    ASSERT_EQ(4, dblArr.size());
    ASSERT_EQ(4.5, dblArr[0]);
    ASSERT_EQ(6.78, dblArr[1]);
    ASSERT_EQ(9, dblArr[2]);
    ASSERT_EQ(10.11, dblArr[3]);

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

    EXPECT_THROW(conf.get_string("foo", "bar"), LogicException);
    EXPECT_THROW(conf.get_locale_string("foo", "bar"), LogicException);
    EXPECT_THROW(conf.get_int("foo", "bar"), LogicException);
    EXPECT_THROW(conf.get_int("first", "doublevalue"), LogicException);
    EXPECT_THROW(conf.get_boolean("foo", "bar"), LogicException);
    EXPECT_THROW(conf.get_int_array("first", "array"), LogicException);
    EXPECT_THROW(conf.get_int_array("second", "doublearray"), LogicException);
    EXPECT_THROW(conf.get_boolean_array("first", "array"), LogicException);
}

TEST(IniParser, writeValues)
{
    // Create an empty ini file for writing
    auto f = fopen(INI_TEMP_FILE, "w");
    fclose(f);

    IniParser conf(INI_TEMP_FILE);

    conf.set_string("g1", "k1", "s0;s1");
    conf.set_locale_string("g1", "k2", "s2", "en");
    conf.set_locale_string("g1", "k2", "s3", "pt_BR");

    // Check temp file before sync()
    {
        IniParser conf2(INI_TEMP_FILE);
        EXPECT_EQ("s0;s1", conf.get_string("g1", "k1"));
        EXPECT_THROW(conf2.get_string("g1", "k1"), LogicException);

        EXPECT_EQ("s2", conf.get_locale_string("g1", "k2", "en"));
        EXPECT_THROW(conf2.get_locale_string("g1", "k2", "en"), LogicException);

        EXPECT_EQ("s3", conf.get_locale_string("g1", "k2", "pt_BR"));
        EXPECT_THROW(conf2.get_locale_string("g1", "k2", "pt_BR"), LogicException);
    }

    // Sync
    conf.sync();

    // Write some post-sync values
    conf.set_boolean("g2", "k1", false);
    conf.set_int("g2", "k2", 123);
    conf.set_double("g3", "k3", 4.56789);

    // Check temp file after first sync()
    {
        IniParser conf2(INI_TEMP_FILE);
        EXPECT_EQ("s0;s1", conf.get_string("g1", "k1"));
        EXPECT_EQ("s0;s1", conf2.get_string("g1", "k1"));

        EXPECT_EQ("s2", conf.get_locale_string("g1", "k2", "en"));
        EXPECT_EQ("s2", conf2.get_locale_string("g1", "k2", "en"));

        EXPECT_EQ("s3", conf.get_locale_string("g1", "k2", "pt_BR"));
        EXPECT_EQ("s3", conf2.get_locale_string("g1", "k2", "pt_BR"));

        EXPECT_EQ(false, conf.get_boolean("g2", "k1"));
        EXPECT_THROW(conf2.get_boolean("g2", "k1"), LogicException);

        EXPECT_EQ(123, conf.get_int("g2", "k2"));
        EXPECT_THROW(conf2.get_int("g2", "k2"), LogicException);

        EXPECT_EQ(4.56789, conf.get_double("g3", "k3"));
        EXPECT_THROW(conf2.get_double("g3", "k3"), LogicException);
    }

    // Sync
    conf.sync();

    // Check temp file after second sync()
    {
        IniParser conf2(INI_TEMP_FILE);
        EXPECT_EQ("s0;s1", conf.get_string("g1", "k1"));
        EXPECT_EQ("s0;s1", conf2.get_string("g1", "k1"));

        EXPECT_EQ("s2", conf.get_locale_string("g1", "k2", "en"));
        EXPECT_EQ("s2", conf2.get_locale_string("g1", "k2", "en"));

        EXPECT_EQ("s3", conf.get_locale_string("g1", "k2", "pt_BR"));
        EXPECT_EQ("s3", conf2.get_locale_string("g1", "k2", "pt_BR"));

        EXPECT_EQ(false, conf.get_boolean("g2", "k1"));
        EXPECT_EQ(false, conf2.get_boolean("g2", "k1"));

        EXPECT_EQ(123, conf.get_int("g2", "k2"));
        EXPECT_EQ(123, conf2.get_int("g2", "k2"));

        EXPECT_EQ(4.56789, conf.get_double("g3", "k3"));
        EXPECT_EQ(4.56789, conf2.get_double("g3", "k3"));
    }
}

template<class T>
void EXPECT_ARRAY_EQ(const vector<T>& expected, const vector<T>& actual)
{
    EXPECT_TRUE(expected == actual);
}

TEST(IniParser, writeArrays)
{
    // Create an empty ini file for writing
    auto f = fopen(INI_TEMP_FILE, "w");
    fclose(f);

    IniParser conf(INI_TEMP_FILE);

    conf.set_string_array("g1", "k1", {"s0;s1", "s2", "s3"});
    conf.set_locale_string_array("g1", "k2", {"s4", "s5", "s6"}, "en");
    conf.set_locale_string_array("g1", "k2", {"s7", "s8", "s9=s10"}, "pt_BR");

    // Check temp file before sync()
    {
        IniParser conf2(INI_TEMP_FILE);
        EXPECT_ARRAY_EQ({"s0;s1", "s2", "s3"}, conf.get_string_array("g1", "k1"));
        EXPECT_THROW(conf2.get_string_array("g1", "k1"), LogicException);

        EXPECT_ARRAY_EQ({"s4", "s5", "s6"}, conf.get_locale_string_array("g1", "k2", "en"));
        EXPECT_THROW(conf2.get_locale_string_array("g1", "k2", "en"), LogicException);

        EXPECT_ARRAY_EQ({"s7", "s8", "s9=s10"}, conf.get_locale_string_array("g1", "k2", "pt_BR"));
        EXPECT_THROW(conf2.get_locale_string_array("g1", "k2", "pt_BR"), LogicException);
    }

    // Sync
    conf.sync();

    // Write some post-sync values
    conf.set_boolean_array("g2", "k1", {true, false, false});
    conf.set_int_array("g2", "k2", {123, 456789, 101112});
    conf.set_double_array("g2", "k3", {13.14, 15.161718, 19.2});

    // Check temp file after first sync()
    {
        IniParser conf2(INI_TEMP_FILE);
        EXPECT_ARRAY_EQ({"s0;s1", "s2", "s3"}, conf.get_string_array("g1", "k1"));
        EXPECT_ARRAY_EQ({"s0;s1", "s2", "s3"}, conf2.get_string_array("g1", "k1"));

        EXPECT_ARRAY_EQ({"s4", "s5", "s6"}, conf.get_locale_string_array("g1", "k2", "en"));
        EXPECT_ARRAY_EQ({"s4", "s5", "s6"}, conf2.get_locale_string_array("g1", "k2", "en"));

        EXPECT_ARRAY_EQ({"s7", "s8", "s9=s10"}, conf.get_locale_string_array("g1", "k2", "pt_BR"));
        EXPECT_ARRAY_EQ({"s7", "s8", "s9=s10"}, conf2.get_locale_string_array("g1", "k2", "pt_BR"));

        EXPECT_ARRAY_EQ({true, false, false}, conf.get_boolean_array("g2", "k1"));
        EXPECT_THROW(conf2.get_boolean_array("g2", "k1"), LogicException);

        EXPECT_ARRAY_EQ({123, 456789, 101112}, conf.get_int_array("g2", "k2"));
        EXPECT_THROW(conf2.get_int_array("g2", "k2"), LogicException);

        EXPECT_ARRAY_EQ({13.14, 15.161718, 19.2}, conf.get_double_array("g2", "k3"));
        EXPECT_THROW(conf2.get_double_array("g2", "k3"), LogicException);
    }

    // Sync
    conf.sync();

    // Check temp file after second sync()
    {
        IniParser conf2(INI_TEMP_FILE);
        EXPECT_ARRAY_EQ({"s0;s1", "s2", "s3"}, conf.get_string_array("g1", "k1"));
        EXPECT_ARRAY_EQ({"s0;s1", "s2", "s3"}, conf2.get_string_array("g1", "k1"));

        EXPECT_ARRAY_EQ({"s4", "s5", "s6"}, conf.get_locale_string_array("g1", "k2", "en"));
        EXPECT_ARRAY_EQ({"s4", "s5", "s6"}, conf2.get_locale_string_array("g1", "k2", "en"));

        EXPECT_ARRAY_EQ({"s7", "s8", "s9=s10"}, conf.get_locale_string_array("g1", "k2", "pt_BR"));
        EXPECT_ARRAY_EQ({"s7", "s8", "s9=s10"}, conf2.get_locale_string_array("g1", "k2", "pt_BR"));

        EXPECT_ARRAY_EQ({true, false, false}, conf.get_boolean_array("g2", "k1"));
        EXPECT_ARRAY_EQ({true, false, false}, conf2.get_boolean_array("g2", "k1"));

        EXPECT_ARRAY_EQ({123, 456789, 101112}, conf.get_int_array("g2", "k2"));
        EXPECT_ARRAY_EQ({123, 456789, 101112}, conf2.get_int_array("g2", "k2"));

        EXPECT_ARRAY_EQ({13.14, 15.161718, 19.2}, conf.get_double_array("g2", "k3"));
        EXPECT_ARRAY_EQ({13.14, 15.161718, 19.2}, conf2.get_double_array("g2", "k3"));
    }
}

TEST(IniParser, writeError)
{
    // Create an empty ini file for writing
    auto f = fopen(INI_TEMP_FILE, "w");
    fclose(f);

    IniParser conf(INI_TEMP_FILE);

    // Replace ini file with a directory
    ASSERT_EQ(0, remove(INI_TEMP_FILE));
    ASSERT_EQ(0, mkdir(INI_TEMP_FILE, 0700));

    std::shared_ptr<void> rmdir_raii(nullptr, [](void*)
    {
        rmdir(INI_TEMP_FILE);
    });

    // Sync (no exception as config is not dirty)
    EXPECT_NO_THROW(conf.sync());

    // Dirty the config
    conf.set_boolean("g1", "k1", true);

    // Sync (exception as target is a directory)
    EXPECT_THROW(conf.sync(), FileException);
}
