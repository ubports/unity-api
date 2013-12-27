/*
 * Copyright (C) 2013 Canonical Ltd
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
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

//
// Simple class to disable copy and assignment. (Provided here to avoid having to use
// the equivalent boost version.)
//
// Use like this:
//
// class MyClass : private util::NonCopyable
// {
//      // ...
// };
//

#ifndef UNITY_UTIL_NONCOPYABLE_H
#define UNITY_UTIL_NONCOPYABLE_H

#include <unity/SymbolExport.h>

namespace unity
{

namespace util
{

namespace NonCopyable_ // Prevent unintended ADL
{

/**
\brief Helper macro to prevent a class from being copied.

This helper macro disables the copy constructor and assignment operator of a class to prevent it
from being copied. This is a macro rather than a base class to reduce clutter on the class
hierarchy.

Use it like this:

class MyClass
{
public: // not necessary, but the error message is more explicit with this
  NONCOPYABLE(MyClass)
  ...
};
*/

#define NONCOPYABLE(ClassName) /** Deleted */ ClassName(ClassName const&) = delete; /** Deleted */ ClassName& operator=(ClassName const&) = delete

/**
 * This class is deprecated and will go away before 14/04 freeze. Use the NONCOPYABLE macro instead or
 * write your own =delete declarations.
 */

class UNITY_API NonCopyable
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

private:
    NonCopyable(NonCopyable const&) = delete;
    NonCopyable& operator=(NonCopyable const&) = delete;
} __attribute__((deprecated));

} // namespace NonCopyable_

typedef NonCopyable_::NonCopyable NonCopyable __attribute__((deprecated));

} // namespace util

} // namespace unity

#endif
