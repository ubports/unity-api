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
 */

#ifndef UNITY_UTIL_GLIBMEMORY_H
#define UNITY_UTIL_GLIBMEMORY_H

#include <memory>
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
}; \
typedef GlibSPtrAssigner<std::shared_ptr<TypeName>> TypeName##SPtrAssigner; \
typedef GlibUPtrAssigner<std::unique_ptr<TypeName, TypeName##Deleter>> TypeName##UPtrAssigner;

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

template<typename U>
class GlibUPtrAssigner
{
public:
    GlibUPtrAssigner(U& uptr) :
            _uptr(uptr)
    {
    }

    GlibUPtrAssigner(const GlibUPtrAssigner& other) = delete;

    ~GlibUPtrAssigner()
    {
        _uptr = unique_glib(_ptr);
    }

    GlibUPtrAssigner operator=(const GlibUPtrAssigner& other) = delete;

    operator typename U::element_type**()
    {
        return &_ptr;
    }

private:
    typename U::element_type* _ptr = nullptr;

    U& _uptr;
};

template<typename S>
class GlibSPtrAssigner
{
public:
    GlibSPtrAssigner(S& sptr) :
            _sptr(sptr)
    {
    }

    GlibSPtrAssigner(const GlibSPtrAssigner& other) = delete;

    ~GlibSPtrAssigner()
    {
        _sptr.reset(_ptr, GlibDeleter<typename S::element_type>());
    }

    GlibSPtrAssigner operator=(const GlibSPtrAssigner& other) = delete;

    operator typename S::element_type**()
    {
        return &_ptr;
    }

private:
    typename S::element_type* _ptr = nullptr;

    S& _sptr;
};

#pragma push_macro("G_DEFINE_AUTOPTR_CLEANUP_FUNC")
#undef G_DEFINE_AUTOPTR_CLEANUP_FUNC
#define G_DEFINE_AUTOPTR_CLEANUP_FUNC(TypeName, func) UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(TypeName, func)

#pragma push_macro("G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC")
#undef G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC
#define G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC(TypeName, func)

#define __GLIB_H_INSIDE__
#include <glib/glib-autocleanups.h>
#undef __GLIB_H_INSIDE__

#pragma pop_macro("G_DEFINE_AUTOPTR_CLEANUP_FUNC")
#pragma pop_macro("G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC")

UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(gchar, g_free)
typedef gchar* gcharv;
UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(gcharv, g_strfreev)

}  // namespace until

}  // namespace unity

#endif
