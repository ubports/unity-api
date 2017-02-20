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

#ifndef UNITY_UTIL_GOBJECTMEMORY_H
#define UNITY_UTIL_GOBJECTMEMORY_H

#include <memory>
#include <stdexcept>
#include <glib-object.h>

namespace unity
{

namespace util
{

namespace
{

inline static void sink_floating_gobject(gpointer t)
{
    if (t != nullptr && g_object_is_floating(G_OBJECT(t)))
    {
        g_object_ref_sink(t);
    }
}

}

/**
 \brief Used by the make_gobject, unique_gobject and share_gobject as the deleter.

 Useful if for some reason the normal helper methods are not suitable for your needs.

 Example:
 \code{.cpp}
 GObjectDeleter d;
 auto shared = shared_ptr<FooBar>(foo_bar_new("name"), d);
 auto unique = unique_ptr<FooBar, GObjectDeleter>(foo_bar_new("name"), d);
 \endcode
 */
struct GObjectDeleter
{
    void operator()(gpointer ptr)
    {
        if (G_IS_OBJECT(ptr) == FALSE)
        {
            return;
        }
        g_object_unref(ptr);
    }
};

/**
 \brief Helper method to wrap a unique_ptr around an existing GObject.

 Useful if the GObject class you are constructing already has a
 dedicated factory from the C library it comes from, and you
 intend to have a unique instance of it.

 Example:
 \code{.cpp}
 auto obj = unique_gobject(foo_bar_new("name"));
 \endcode
 */
template<typename T>
inline std::unique_ptr<T, GObjectDeleter> unique_gobject(T* ptr)
{
    sink_floating_gobject(ptr);
    GObjectDeleter d;
    return std::unique_ptr<T, GObjectDeleter>(ptr, d);
}

/**
 \brief Helper method to wrap a shared_ptr around an existing GObject.

 Useful if the GObject class you are constructing already has a
 dedicated factory from the C library it comes from, and you
 intend to share it.

 Example:
 \code{.cpp}
 auto obj = share_gobject(foo_bar_new("name"));
 \endcode
 */
template<typename T>
inline std::shared_ptr<T> share_gobject(T* ptr)
{
    sink_floating_gobject(ptr);
    GObjectDeleter d;
    return std::shared_ptr<T>(ptr, d);
}

/**
 \brief Helper method to construct a gobj_ptr-wrapped GObject class.

 Uses the same signature as the g_object_new() method.

 Example:
 \code{.cpp}
 auto obj = make_gobject<FooBar>(FOO_TYPE_BAR, "name", "banana", nullptr);
 \endcode
 */
template<typename T, typename ... Args>
inline std::unique_ptr<T, GObjectDeleter> make_gobject(GType object_type, const gchar *first_property_name, Args&&... args)
{
    gpointer ptr = g_object_new(object_type, first_property_name, std::forward<Args>(args)...);
    return unique_gobject(G_TYPE_CHECK_INSTANCE_CAST(ptr, object_type, T));
}

}  // namespace until

}  // namespace unity

#endif
