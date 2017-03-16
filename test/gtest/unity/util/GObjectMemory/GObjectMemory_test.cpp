/*
 * Copyright (C) 2013-2017 Canonical Ltd.
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
 *              Pete Woods <pete.woods@canonical.com>
 */

#include <unity/util/GObjectMemory.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <list>
#include <string>
#include <unordered_set>

using namespace std;
using namespace unity::util;

namespace
{

typedef pair<string, int> Deleted;
static list<Deleted> DELETED_OBJECTS;

//
// Below here is a basic implementation of a GObject type
//

// "public" header

G_BEGIN_DECLS

#define FOO_TYPE_BAR foo_bar_get_type()
G_DECLARE_FINAL_TYPE (FooBar, foo_bar, FOO, BAR, GObject)

FooBar *foo_bar_new();

FooBar *foo_bar_new_full(const gchar* const name, guint id);

G_END_DECLS

// private implementation

struct _FooBar
{
    GObject parent_instance;

    gchar *name;

    guint id;
};

G_DEFINE_TYPE (FooBar, foo_bar, G_TYPE_OBJECT)

enum
{
    PROP_NAME = 1,
    PROP_ID,
    N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void foo_bar_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
    FooBar *self = FOO_BAR(object);

    switch (property_id)
    {
    case PROP_NAME:
        g_free(self->name);
        self->name = g_value_dup_string(value);
        break;

    case PROP_ID:
        self->id = g_value_get_uint(value);
        break;

    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

static void foo_bar_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
    FooBar *self = FOO_BAR(object);

    switch (property_id)
    {
    case PROP_NAME:
        g_value_set_string(value, self->name);
        break;

    case PROP_ID:
        g_value_set_uint(value, self->id);
        break;

    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

static void foo_bar_finalize(GObject *gobject)
{
    FooBar* self = FOO_BAR(gobject);

    DELETED_OBJECTS.emplace_back(Deleted(string(self->name == NULL ? "" : self->name), self->id));

    g_free(self->name);

    G_OBJECT_CLASS (foo_bar_parent_class)->finalize(gobject);
}

static void foo_bar_class_init(FooBarClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->set_property = foo_bar_set_property;
    object_class->get_property = foo_bar_get_property;
    object_class->finalize = foo_bar_finalize;

    obj_properties[PROP_NAME] =
      g_param_spec_string ("name",
                           "Name",
                           "Name of the file to load and display from.",
                           "default-name"  /* default value */,
                           (GParamFlags) (G_PARAM_READWRITE));

    obj_properties[PROP_ID] =
      g_param_spec_uint ("id",
                         "ID",
                         "ID of this dummy class",
                         0  /* minimum value */,
                         10 /* maximum value */,
                         2  /* default value */,
                         (GParamFlags) G_PARAM_READWRITE);

    g_object_class_install_properties (object_class,
                                       N_PROPERTIES,
                                       obj_properties);
}

static void foo_bar_init(FooBar *)
{
}

FooBar *foo_bar_new()
{
    return FOO_BAR(g_object_new(FOO_TYPE_BAR, NULL));
}

FooBar *foo_bar_new_full(const gchar* const name, guint id)
{
    return FOO_BAR(g_object_new(FOO_TYPE_BAR, "name", name, "id", id, NULL));
}

//
// Test cases
//

class GObjectMemoryTest: public testing::Test
{
protected:
    static void SetUpTestCase()
    {
        g_log_set_always_fatal((GLogLevelFlags) (G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL));
    }

    void SetUp() override
    {
        DELETED_OBJECTS.clear();
    }
};

TEST_F(GObjectMemoryTest, trivial)
{
    auto basic = unique_gobject(foo_bar_new());
    EXPECT_TRUE(bool(basic));
    EXPECT_TRUE(G_IS_OBJECT(basic.get()));
}

TEST_F(GObjectMemoryTest, compare)
{
    FooBar* o1 = foo_bar_new();
    FooBar* o2 = foo_bar_new();
    if (o1 > o2) {
        std::swap(o1, o2);
    }
    ASSERT_TRUE(o1 < o2);
    auto u1 = unique_gobject(o1);
    auto u2 = unique_gobject(o2);

    EXPECT_TRUE(!(u1 == nullptr));
    EXPECT_TRUE(u1 != nullptr);
    EXPECT_TRUE(u1 != u2);
    EXPECT_TRUE(!(u1 == u2));
    EXPECT_TRUE(u1 < u2);
    EXPECT_TRUE(!(u2 < u1));
    EXPECT_TRUE(!(u1 == u2));
    EXPECT_TRUE(!(u2 == u1));
    EXPECT_TRUE(u1 <= u2);
    EXPECT_TRUE(!(u2 <= u1));
}

// This is its own thing due to need to avoid double release.

TEST_F(GObjectMemoryTest, equality)
{
    FooBar* o = foo_bar_new();
    auto u1 = unique_gobject(o);
    g_object_ref(o);
    auto u2 = unique_gobject(o);
    EXPECT_TRUE(u1 == u2);
    EXPECT_TRUE(u2 == u1);
    EXPECT_TRUE(!(u1 != u2));
    EXPECT_TRUE(!(u2 != u1));
}

TEST_F(GObjectMemoryTest, release)
{
    FooBar* o = foo_bar_new();
    auto u = unique_gobject(o);
    EXPECT_TRUE(u != nullptr);
    EXPECT_TRUE(u.get() != nullptr);
    EXPECT_TRUE(o == u.release());
    EXPECT_TRUE(!u);
    EXPECT_TRUE(u.get() == nullptr);
    g_object_unref(o);
}

TEST_F(GObjectMemoryTest, refcount)
{
    GObject* o = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    EXPECT_EQ(1, o->ref_count);
    g_object_ref(o);

    {
        EXPECT_EQ(2, o->ref_count);
        auto u = unique_gobject<GObject>(o);
        EXPECT_EQ(2, o->ref_count);
        // Now it dies and refcount is reduced.
    }

    EXPECT_EQ(1, o->ref_count);
    g_object_unref(o);
}

TEST_F(GObjectMemoryTest, swap)
{
    FooBar* o1 = foo_bar_new();
    FooBar* o2 = foo_bar_new();
    auto u1 = unique_gobject(o1);
    auto u2 = unique_gobject(o2);

    u1.swap(u2);
    EXPECT_EQ(o2, u1.get());
    EXPECT_EQ(o1, u2.get());

    std::swap(u1, u2);
    EXPECT_EQ(o1, u1.get());
    EXPECT_EQ(o2, u2.get());
}

TEST_F(GObjectMemoryTest, floating)
{
    {
        auto o = G_INITIALLY_UNOWNED(g_object_new(G_TYPE_INITIALLY_UNOWNED, nullptr));
        EXPECT_THROW(unique_gobject(o), invalid_argument);
        g_object_ref_sink(G_OBJECT(o));
        unique_gobject(o);
    }
    {
        auto o = G_INITIALLY_UNOWNED(g_object_new(G_TYPE_INITIALLY_UNOWNED, nullptr));
        EXPECT_THROW(unique_gobject(o), invalid_argument);
        g_object_ref_sink(G_OBJECT(o));
        unique_gobject(o);
    }

    EXPECT_THROW(make_gobject<GInitiallyUnowned>(G_TYPE_INITIALLY_UNOWNED, nullptr), invalid_argument);
}

TEST_F(GObjectMemoryTest, move)
{
    GObject* o1 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    GObject* o2 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    g_object_ref(o1);
    auto u1 = unique_gobject<GObject>(o1);
    auto u2 = unique_gobject<GObject>(o2);
    u1 = std::move(u2);
    EXPECT_TRUE(u1.get() == o2);
    EXPECT_TRUE(!u2);
    EXPECT_TRUE(o1->ref_count == 1);
    g_object_unref(o1);
}

TEST_F(GObjectMemoryTest, null)
{
    FooBar* o1 = NULL;
    FooBar* o3 = foo_bar_new();
    auto u1 = unique_gobject(o1);
    auto u2 = unique_gobject<FooBar>(nullptr);
    auto u3 = unique_gobject(o3);
    auto u4 = unique_gobject((FooBar *) NULL);

    EXPECT_TRUE(!u1);
    EXPECT_TRUE(!u2);
    u3 = nullptr;
    EXPECT_TRUE(!u3);
}

TEST_F(GObjectMemoryTest, reset)
{
    FooBar* o1 = foo_bar_new();
    FooBar* o2 = foo_bar_new();
    auto u = unique_gobject(o1);

    u.reset(o2);
    EXPECT_EQ(o2, u.get());
    u.reset(nullptr);
    EXPECT_TRUE(!u);
}

TEST_F(GObjectMemoryTest, sizeoftest) {
    EXPECT_EQ(sizeof(FooBar*), sizeof(unique_ptr<FooBar>));
}

TEST_F(GObjectMemoryTest, hash)
{
    unordered_set<shared_ptr<FooBar>> s;
    auto a = share_gobject(foo_bar_new());
    auto b = share_gobject(foo_bar_new());
    auto c = share_gobject(foo_bar_new());

    s.emplace(a);
    EXPECT_EQ(1, s.size());
    EXPECT_FALSE(s.end() == s.find(a));

    s.emplace(b);
    EXPECT_EQ(2, s.size());
    EXPECT_FALSE(s.end() == s.find(b));

    s.emplace(c);
    EXPECT_EQ(3, s.size());
    EXPECT_FALSE(s.end() == s.find(c));

    // Shouldn't add the duplicates
    s.emplace(a);
    s.emplace(b);
    s.emplace(c);
    EXPECT_EQ(3, s.size());

    s.erase(a);
    EXPECT_EQ(2, s.size());

    s.erase(b);
    EXPECT_EQ(1, s.size());

    s.erase(c);
    EXPECT_TRUE(s.empty());
}

TEST_F(GObjectMemoryTest, uniquePtrDeletesGObjects)
{
    {
        auto a = unique_gobject(foo_bar_new_full("a", 1));
        auto b = unique_gobject(foo_bar_new_full("b", 2));
    }
    EXPECT_EQ(list<Deleted>({{"b", 2}, {"a", 1}}), DELETED_OBJECTS);
}

TEST_F(GObjectMemoryTest, sharedPtrDeletesGObjects)
{
    {
        auto a = share_gobject(foo_bar_new_full("a", 1));
        auto b = share_gobject(foo_bar_new_full("b", 2));
    }
    EXPECT_EQ(list<Deleted>({{"b", 2}, {"a", 1}}), DELETED_OBJECTS);
}

TEST_F(GObjectMemoryTest, makeGObjectDeletesGObjects)
{
    {
        auto a = make_gobject<FooBar>(FOO_TYPE_BAR, "name", "a", "id", 1, nullptr);
        auto b = make_gobject<FooBar>(FOO_TYPE_BAR, "name", "b", "id", 2, nullptr);
        auto c = make_gobject<FooBar>(FOO_TYPE_BAR, "name", "c", "id", 3, nullptr);
    }
    EXPECT_EQ(list<Deleted>({{"c", 3}, {"b", 2}, {"a", 1}}), DELETED_OBJECTS);
}

TEST_F(GObjectMemoryTest, foo)
{
    {
        shared_ptr<FooBar> s;
        auto u = unique_gobject(foo_bar_new_full("hi", 6));
        s = move(u);
        // unique instance has been stolen from
        EXPECT_FALSE(u);
    }
    EXPECT_EQ(list<Deleted>({{"hi", 6}}), DELETED_OBJECTS);
    {
        shared_ptr<FooBar> s(unique_gobject(foo_bar_new_full("bye", 7)));
    }
    EXPECT_EQ(list<Deleted>({{"hi", 6}, {"bye", 7}}), DELETED_OBJECTS);
}

typedef pair<const char*, guint> GObjectMemoryMakeSharedTestParam;

class GObjectMemoryMakeHelperMethodsTest: public testing::TestWithParam<GObjectMemoryMakeSharedTestParam>
{
protected:
    /**
     * We test for multiple properties so that we can be sure the various
     * helper methods correctly pass through different data types and
     * multiple combinations of arguments correctly.
     */
    static void checkProperties(gpointer obj, const char* expectedName, guint expectedId)
    {
        char* name = NULL;
        guint id = 0;

        g_object_get(obj, "name", &name, "id", &id, NULL);
        EXPECT_STREQ(expectedName, name);
        EXPECT_EQ(expectedId, id);

        g_free(name);
    }
};

TEST_P(GObjectMemoryMakeHelperMethodsTest, make_gobject_passes_arguments)
{
    auto p = GetParam();
    auto obj = make_gobject<FooBar>(FOO_TYPE_BAR, "name", p.first, "id", p.second, nullptr);
    checkProperties(obj.get(), p.first, p.second);
}

TEST_P(GObjectMemoryMakeHelperMethodsTest, make_gobject_no_arguments)
{
    auto p = GetParam();
    auto obj = make_gobject<FooBar>(FOO_TYPE_BAR, nullptr);
    g_object_set(obj.get(), "name", p.first, "id", p.second, nullptr);
    checkProperties(obj.get(), p.first, p.second);
}

TEST_P(GObjectMemoryMakeHelperMethodsTest, unique_foo_bar_new)
{
    auto p = GetParam();
    auto obj = unique_gobject(foo_bar_new_full(p.first,p.second));
    checkProperties(obj.get(), p.first, p.second);
}

TEST_P(GObjectMemoryMakeHelperMethodsTest, share_foo_bar_new)
{
    auto p = GetParam();
    auto obj = share_gobject(foo_bar_new_full(p.first, p.second));
    checkProperties(obj.get(), p.first, p.second);
}

INSTANTIATE_TEST_CASE_P(BunchOfNames,
                        GObjectMemoryMakeHelperMethodsTest,
                        ::testing::Values(GObjectMemoryMakeSharedTestParam{"meeny", 1},
                                          GObjectMemoryMakeSharedTestParam{"miny", 2},
                                          GObjectMemoryMakeSharedTestParam{"moe", 3}));

}
