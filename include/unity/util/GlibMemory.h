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

#pragma push_macro("G_DEFINE_AUTOPTR_CLEANUP_FUNC")
#undef G_DEFINE_AUTOPTR_CLEANUP_FUNC
#define G_DEFINE_AUTOPTR_CLEANUP_FUNC(TypeName, func) \
inline std::shared_ptr<TypeName> share_glib(TypeName* ptr) \
{ \
    return std::shared_ptr<TypeName>(ptr, &func); \
} \
inline std::unique_ptr<TypeName, decltype(&func)> unique_glib(TypeName* ptr) \
{ \
    return std::unique_ptr<TypeName, decltype(&func)>(ptr, &func); \
}

#pragma push_macro("G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC")
#undef G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC
#define G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC(TypeName, func)

#define __GLIB_H_INSIDE__
#include <glib/glib-autocleanups.h>
#undef __GLIB_H_INSIDE__

#pragma pop_macro("G_DEFINE_AUTOPTR_CLEANUP_FUNC")
#pragma pop_macro("G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC")

}  // namespace until

}  // namespace unity

#endif
