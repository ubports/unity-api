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
#include <type_traits>
#include <glib.h>

namespace unity
{

namespace util
{

template<typename T> struct GlibDeleter;

#define UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(TypeName, func) \
typedef GlibDeleter<TypeName> TypeName##Deleter; \
typedef std::shared_ptr<TypeName> TypeName##SPtr; \
typedef std::unique_ptr<TypeName, TypeName##Deleter> TypeName##UPtr; \
template<> struct GlibDeleter<TypeName> \
{ \
    void operator()(TypeName* ptr) \
    { \
        if (ptr) \
        { \
            ::func(ptr); \
        } \
    } \
};

template<typename T>
inline std::shared_ptr<T> share_glib(T* ptr)
{
    return std::shared_ptr<T>(ptr, GlibDeleter<T>());
}

template<typename T>
inline std::unique_ptr<T, GlibDeleter<T>> unique_glib(T* ptr)
{
    return std::unique_ptr<T, GlibDeleter<T>>(ptr, GlibDeleter<T>());
}

// Adapter class that allows passing a shared_ptr or unique_ptr where glib
// expects a parameter of type ElementType** (such as GError**), by providing
// a default conversion operator to ElementType**. This allows the glib method
// to assign to the ptr_ member. From the destructor, we call the appropriate
// reset() method to trigger a call to the smart pointer's deleter, which
// invokes the the appropriate glib deleter (such as g_error_free()).

template<typename SP>
class GlibPtrAssigner
{
public:
    typedef typename SP::element_type ElementType;

    GlibPtrAssigner(SP& smart_ptr)
        : smart_ptr_(smart_ptr)
    {
    }

    GlibPtrAssigner(const GlibPtrAssigner& other) = delete;

    GlibPtrAssigner(GlibPtrAssigner&& other)
        : ptr_(other.ptr_)
        , smart_ptr_(other.smart_ptr_)
    {
        other.smart_ptr_ = nullptr;
    }

    ~GlibPtrAssigner()
    {
        release<SP>(smart_ptr_, ptr_);
    }

    GlibPtrAssigner operator=(const GlibPtrAssigner& other) = delete;

    operator ElementType**()
    {
        return &ptr_;
    }

private:
    // Instantiate exactly one of the two release() methods below, depending
    // on whether we were instantiated with a shared_ptr or a unique_ptr.

    template<typename T> 
    typename std::enable_if<
        std::is_same<T, std::shared_ptr<typename T::element_type>>::value,
        void
    >::type
    release(std::shared_ptr<ElementType>& smart, ElementType* p)
    {
        smart.reset(p, GlibDeleter<typename T::element_type>());
    }

    template<typename T> 
    typename std::enable_if<
        std::is_same<T, std::unique_ptr<typename T::element_type, typename T::deleter_type>>::value,
        void
    >::type
    release(std::unique_ptr<ElementType, GlibDeleter<typename T::element_type>>& smart, ElementType* p)
    {
        smart.reset(p);
    }

    ElementType* ptr_ = nullptr;
    SP& smart_ptr_;
};

template<typename SP>
inline
GlibPtrAssigner<SP> glib_assign(SP& smart_ptr)
{
    return GlibPtrAssigner<SP>(smart_ptr);
}

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

UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(gchar, g_free)
typedef gchar* gcharv;
UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(gcharv, g_strfreev)

}  // namespace until

}  // namespace unity

#endif
