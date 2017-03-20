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
    static void SetUpTestCase()
    {
        g_log_set_always_fatal((GLogLevelFlags) (G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL));
    }

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

    static GKeyFileUPtr newGKeyFile()
    {
        return unique_glib(g_key_file_new());
    }

    static GVariantUPtr newGVariant(const gchar* const value)
    {
        return unique_glib(g_variant_new_string(value));
    }

    static GHashTableUPtr newGHashTable()
    {
        return unique_glib(g_hash_table_new_full(g_str_hash, g_str_equal, deleteKey, deleteValue));
    }

    static GKeyFileSPtr sharedGKeyFile()
    {
        return share_glib(g_key_file_new());
    }

    static GVariantSPtr sharedGVariant(const gchar* const value)
    {
        return share_glib(g_variant_new_string(value));
    }

    static GHashTableSPtr sharedGHashTable()
    {
        return share_glib(g_hash_table_new_full(g_str_hash, g_str_equal, deleteKey, deleteValue));
    }
};

TEST_F(GlibMemoryTest, Unique)
{
    {
        auto gkf = newGKeyFile();
        g_key_file_set_boolean(gkf.get(), "group", "key", TRUE);
        EXPECT_EQ(TRUE, g_key_file_get_boolean(gkf.get(), "group", "key", NULL));
    }

    {
        auto variant = newGVariant("hello");
        EXPECT_STREQ("hello", g_variant_get_string(variant.get(), NULL));
    }

    {
        {
            auto hash = newGHashTable();
            g_hash_table_insert(hash.get(), (gpointer) "hello", (gpointer) "there");
            g_hash_table_insert(hash.get(), (gpointer) "hash", (gpointer) "world");
        }
        EXPECT_EQ(set<string>({"hello", "hash"}), keys);
        EXPECT_EQ(set<string>({"there", "world"}), values);
    }

    {
        auto emptyVariant = unique_glib((GVariant*) NULL);
    }
}

TEST_F(GlibMemoryTest, Share)
{
    {
        auto gkf = sharedGKeyFile();
        g_key_file_set_boolean(gkf.get(), "group", "key", TRUE);
        EXPECT_EQ(TRUE, g_key_file_get_boolean(gkf.get(), "group", "key", NULL));
    }

    {
        auto variant = sharedGVariant("hello");
        EXPECT_STREQ("hello", g_variant_get_string(variant.get(), NULL));
    }

    {
        {
            auto hash = sharedGHashTable();
            g_hash_table_insert(hash.get(), (gpointer) "hello", (gpointer) "there");
            g_hash_table_insert(hash.get(), (gpointer) "hash", (gpointer) "world");
        }
        EXPECT_EQ(set<string>({"hello", "hash"}), keys);
        EXPECT_EQ(set<string>({"there", "world"}), values);
    }

    {
        auto emptyVariant = share_glib((GVariant*) NULL);
    }
}

TEST_F(GlibMemoryTest, Assigner)
{
    auto gkf = unique_glib(g_key_file_new());

    {
        GErrorUPtr error;
        EXPECT_FALSE(g_key_file_get_boolean(gkf.get(), "group", "key", GErrorAssigner(error)));
        ASSERT_TRUE(bool(error));
        EXPECT_EQ(G_KEY_FILE_ERROR_GROUP_NOT_FOUND, error->code);
    }

    g_key_file_set_boolean(gkf.get(), "group", "key", TRUE);

    {
        GErrorUPtr error;
        EXPECT_TRUE(g_key_file_get_boolean(gkf.get(), "group", "key", GErrorAssigner(error)));
        EXPECT_FALSE(bool(error));
    }
}

}
