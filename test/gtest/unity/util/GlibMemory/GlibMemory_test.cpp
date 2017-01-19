/*
 * Copyright (C) 2017 Canonical Ltd
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
 * Authored by: Pete Woods <pete.woods@canonical.com>
 */

#include <unity/util/GlibMemory.h>

#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include <string>

using namespace std;
using namespace unity;
using namespace unity::util;

namespace
{

static set<string> keys;

static set<string> values;

class GlibMemoryTest: public testing::Test
{
protected:
    void SetUp() override
    {
        keys.clear();
        values.clear();
    }

    static void deleteKey(gpointer data)
    {
        // Note that we don't g_free the data, because it's a reference to a static string
        keys.emplace(string((gchar*) data));
    }

    static void deleteValue(gpointer data)
    {
        // Note that we don't g_free the data, because it's a reference to a static string
        values.emplace(string((gchar*) data));
    }
};

TEST_F(GlibMemoryTest, Unique)
{
    {
        auto gkf = unique_glib(g_key_file_new());
        g_key_file_set_boolean(gkf.get(), "group", "key", TRUE);
        EXPECT_EQ(TRUE, g_key_file_get_boolean(gkf.get(), "group", "key", NULL));
    }

    {
        auto variant = unique_glib(g_variant_new_string("hello"));
        EXPECT_STREQ("hello", g_variant_get_string(variant.get(), NULL));
    }

    {
        {
            auto hash = unique_glib(g_hash_table_new_full(g_str_hash, g_str_equal, deleteKey, deleteValue));
            g_hash_table_insert(hash.get(), (gpointer) "hello", (gpointer) "there");
            g_hash_table_insert(hash.get(), (gpointer) "hash", (gpointer) "world");
        }
        EXPECT_EQ(set<string>({"hello", "hash"}), keys);
        EXPECT_EQ(set<string>({"there", "world"}), values);
    }
}

TEST_F(GlibMemoryTest, Share)
{
    {
        auto gkf = share_glib(g_key_file_new());
        g_key_file_set_boolean(gkf.get(), "group", "key", TRUE);
        EXPECT_EQ(TRUE, g_key_file_get_boolean(gkf.get(), "group", "key", NULL));
    }

    {
        auto variant = share_glib(g_variant_new_string("hello"));
        EXPECT_STREQ("hello", g_variant_get_string(variant.get(), NULL));
    }

    {
        {
            auto hash = share_glib(g_hash_table_new_full(g_str_hash, g_str_equal, deleteKey, deleteValue));
            g_hash_table_insert(hash.get(), (gpointer) "hello", (gpointer) "there");
            g_hash_table_insert(hash.get(), (gpointer) "hash", (gpointer) "world");
        }
        EXPECT_EQ(set<string>({"hello", "hash"}), keys);
        EXPECT_EQ(set<string>({"there", "world"}), values);
    }
}

}
