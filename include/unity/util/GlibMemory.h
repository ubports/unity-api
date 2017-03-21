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
 */

#ifndef UNITY_UTIL_GLIBMEMORY_H
#define UNITY_UTIL_GLIBMEMORY_H

#include <memory>
#include <glib.h>

namespace unity
{

namespace util
{

template<typename T, typename D>
struct GlibDeleter
{
    D _d;

    void operator()(T* ptr)
    {
        if (ptr != nullptr)
        {
            _d(ptr);
        }
    }
};

#define UNITY_UTIL_DEFINE_GLIB_SMART_POINTERS(TypeName, func) \
typedef GlibDeleter<TypeName, decltype(&func)> TypeName##Deleter; \
typedef std::shared_ptr<TypeName> TypeName##SPtr; \
inline TypeName##SPtr share_glib(TypeName* ptr) \
{ \
    return TypeName##SPtr(ptr, TypeName##Deleter{&func}); \
} \
typedef std::unique_ptr<TypeName, TypeName##Deleter> TypeName##UPtr; \
inline TypeName##UPtr unique_glib(TypeName* ptr) \
{ \
    return TypeName##UPtr(ptr, TypeName##Deleter{&func}); \
} \
class TypeName##Assigner \
{ \
public: \
    TypeName##Assigner(TypeName##UPtr& uptr) : \
        _uptr(uptr) \
    { \
    } \
    TypeName##Assigner(const TypeName##Assigner& other) = delete; \
    ~TypeName##Assigner() \
    { \
        _uptr = unique_glib(_ptr); \
    } \
    TypeName##Assigner operator=(const TypeName##Assigner& other) = delete; \
    operator TypeName**() \
    { \
        return &_ptr; \
    } \
private: \
    TypeName* _ptr = nullptr; \
    TypeName##UPtr& _uptr; \
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
