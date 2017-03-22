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

inline static void check_floating_gobject(gpointer t)
{
    if (G_IS_OBJECT(t) && g_object_is_floating(G_OBJECT(t)))
    {
        throw std::invalid_argument("cannot manage floating GObject reference - call g_object_ref_sink(o) first");
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
        if (G_IS_OBJECT(ptr))
        {
            g_object_unref(ptr);
        }
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
    check_floating_gobject(ptr);
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
    check_floating_gobject(ptr);
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
    if (G_IS_OBJECT(ptr) && g_object_is_floating(ptr))
    {
        g_object_ref_sink(ptr);
    }
    return unique_gobject(G_TYPE_CHECK_INSTANCE_CAST(ptr, object_type, T));
}

template<typename U>
class GObjectUPtrAssigner
{
public:
    GObjectUPtrAssigner(U& uptr) :
        _uptr(uptr)
    {
    }

    GObjectUPtrAssigner(const GObjectUPtrAssigner& other) = delete;

    GObjectUPtrAssigner(GObjectUPtrAssigner&& other) :
        _ptr(other._ptr), _uptr(other._uptr)
    {
        other._ptr = nullptr;
    }

    ~GObjectUPtrAssigner()
    {
        _uptr = unique_gobject(_ptr);
    }

    GObjectUPtrAssigner operator=(const GObjectUPtrAssigner& other) = delete;

    operator typename U::element_type**()
    {
        return &_ptr;
    }

private:
    typename U::element_type* _ptr = nullptr;

    U& _uptr;
};

template<typename S>
class GObjectSPtrAssigner
{
public:
    GObjectSPtrAssigner(S& sptr) :
        _sptr(sptr)
    {
    }

    GObjectSPtrAssigner(const GObjectSPtrAssigner& other) = delete;

    GObjectSPtrAssigner(GObjectSPtrAssigner&& other) :
        _ptr(other._ptr), _sptr(other._sptr)
    {
        other._ptr = nullptr;
    }

    ~GObjectSPtrAssigner()
    {
        if (_ptr)
        {
            _sptr.reset(_ptr, GObjectDeleter());
        }
    }

    GObjectSPtrAssigner operator=(const GObjectSPtrAssigner& other) = delete;

    operator typename S::element_type**()
    {
        return &_ptr;
    }

private:
    typename S::element_type* _ptr = nullptr;

    S& _sptr;
};

template<typename U>
inline GObjectUPtrAssigner<U> gobject_assign_uptr(U& uptr)
{
    return GObjectUPtrAssigner<U>(uptr);
}

template<typename S>
inline GObjectSPtrAssigner<S> gobject_assign_sptr(S& sptr)
{
    return GObjectSPtrAssigner<S>(sptr);
}

}  // namespace until

}  // namespace unity

#endif
