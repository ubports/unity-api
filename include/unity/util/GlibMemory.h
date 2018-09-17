/*
 * Copyright (C) 2017 Canonical Ltd.
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
 *              Michi Henning <michi.henning@canonical.com>
 *              James Henstridge <james.henstridge@canonical.com>
 */

#ifndef UNITY_UTIL_GLIBMEMORY_H
#define UNITY_UTIL_GLIBMEMORY_H

#include <memory>
#include <glib.h>

#include <unity/util/ResourcePtr.h>

namespace unity
{

namespace util
{

namespace internal
{

template<typename T> struct GlibDeleter;
template<typename T> using GlibSPtr = std::shared_ptr<T>;
template<typename T> using GlibUPtr = std::unique_ptr<T, GlibDeleter<T>>;

/**
 * \brief Adapter class to assign to smart pointers from functions that take a reference.
 *
 * Adapter class that allows passing a shared_ptr or unique_ptr where glib
 * expects a parameter of type ElementType** (such as GError**), by providing
 * a default conversion operator to ElementType**. This allows the glib method
 * to assign to the ptr_ member. From the destructor, we assign to the
 * provided smart pointer.
 */
template<typename SP>
class GlibAssigner
{
public:
    typedef typename SP::element_type ElementType;

    GlibAssigner(SP& smart_ptr) noexcept :
            smart_ptr_(smart_ptr)
    {
    }

    GlibAssigner(const GlibAssigner& other) = delete;

    GlibAssigner(GlibAssigner&& other) noexcept:
            ptr_(other.ptr_), smart_ptr_(other.smart_ptr_)
    {
        other.ptr_ = nullptr;
    }

    ~GlibAssigner() noexcept
    {
        smart_ptr_ = SP(ptr_, GlibDeleter<ElementType>());
    }

    GlibAssigner& operator=(const GlibAssigner& other) = delete;

    operator ElementType**() noexcept
    {
        return &ptr_;
    }

private:
    ElementType* ptr_ = nullptr;

    SP& smart_ptr_;
};

struct GSourceUnsubscriber
{
    void operator()(guint tag) noexcept
    {
        if (tag != 0)
        {
            g_source_remove(tag);
        }
    }
};

}

#define UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(TypeName, func) \
using TypeName##Deleter = internal::GlibDeleter<TypeName>; \
using TypeName##SPtr = internal::GlibSPtr<TypeName>; \
using TypeName##UPtr = internal::GlibUPtr<TypeName>; \
namespace internal \
{ \
template<> struct GlibDeleter<TypeName> \
{ \
    void operator()(TypeName* ptr) noexcept \
    { \
        if (ptr) \
        { \
            ::func(ptr); \
        } \
    } \
}; \
}

/**
 \brief Helper method to wrap a shared_ptr around a Glib type.

 Example:
 \code{.cpp}
 auto gkf = shared_glib(g_key_file_new());
 \endcode
 */
template<typename T>
inline internal::GlibSPtr<T> share_glib(T* ptr) noexcept
{
    return internal::GlibSPtr<T>(ptr, internal::GlibDeleter<T>());
}

/**
 \brief Helper method to wrap a unique_ptr around a Glib type.

 Example:
 \code{.cpp}
 auto gkf = unique_glib(g_key_file_new());
 \endcode
 */
template<typename T>
inline internal::GlibUPtr<T> unique_glib(T* ptr) noexcept
{
    return internal::GlibUPtr<T>(ptr, internal::GlibDeleter<T>());
}

/**
 \brief Helper method to take ownership of glib types assigned from a reference.

 Example:
 \code{.cpp}
 GErrorUPtr error;
 if (!g_key_file_get_boolean(gkf.get(), "group", "key", assign_glib(error)))
 {
     std::cerr << error->message << std::endl;
     throw some_exception();
 }
 \endcode

 Another example:
 \code{.cpp}
 gcharUPtr name;
 g_object_get(obj, "name", assign_glib(name), nullptr);
 \endcode
 */
template<typename SP>
inline internal::GlibAssigner<SP> assign_glib(SP& smart_ptr) noexcept
{
    return internal::GlibAssigner<SP>(smart_ptr);
}

using GSourceManager = ResourcePtr<guint, internal::GSourceUnsubscriber>;

/**
 \brief Simple wrapper to manage the lifecycle of sources.

 When 'timer' goes out of scope or is dealloc'ed, the source will be removed:
 \code{.cpp}
 auto timer = g_source_manager(g_timeout_add(5000, on_timeout, nullptr));
 \endcode
 */
inline GSourceManager g_source_manager(guint id)
{
    return GSourceManager(id, internal::GSourceUnsubscriber());
}

/**
 * Below here is some hackery to extract the matching deleters for all built in glib types.
 */
#pragma push_macro("G_DEFINE_AUTOPTR_CLEANUP_FUNC")
#undef G_DEFINE_AUTOPTR_CLEANUP_FUNC
#define G_DEFINE_AUTOPTR_CLEANUP_FUNC(TypeName, func) UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(TypeName, func)

#pragma push_macro("G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC")
#undef G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC
#define G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC(TypeName, func)

#pragma push_macro("G_DEFINE_AUTO_CLEANUP_FREE_FUNC")
#undef G_DEFINE_AUTO_CLEANUP_FREE_FUNC
#define G_DEFINE_AUTO_CLEANUP_FREE_FUNC(TypeName, func, none)

#define __GLIB_H_INSIDE__
#include <glib/glib-autocleanups.h>
#undef __GLIB_H_INSIDE__

#pragma pop_macro("G_DEFINE_AUTOPTR_CLEANUP_FUNC")
#pragma pop_macro("G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC")
#pragma pop_macro("G_DEFINE_AUTO_CLEANUP_FREE_FUNC")

/**
 * Manually add extra definitions for gchar* and gchar**
 */
#if !GLIB_CHECK_VERSION(2, 57, 2)
UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(gchar, g_free)
#endif
typedef gchar* gcharv;
UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(gcharv, g_strfreev)

}  // namespace until

}  // namespace unity

#endif
