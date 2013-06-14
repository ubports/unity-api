/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
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
\brief Helper class to prevent a class from being copied.

This class disables the copy constructor and assignment operator of a class to prevent it from being copied.
This makes the fact that a class is not copyable immediately visible on reading the class definition,
rather than having to read through the entire class to look for a copy constructor and assignment operator
in the private section, or having to look for <code> = delete;</code> on the corresponding definitions.

To use the class, use private inheritance:
~~~
* class MyClass : private unity::util::NonCopyable
* {
* public:
*     // MyClass cannot be copied now
*     // ...
* };
~~~

\note Do not use public or protected inheritance for this class. Private inheritance prevents accidental polymorphism, such as
~~~
* void some_method(NonCopyable& param); // Bad, permits unrelated classes to be passed
~~~

*/

class UNITY_API NonCopyable
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

private:
    NonCopyable(NonCopyable const&) = delete;
    NonCopyable& operator=(NonCopyable const&) = delete;
};

} // namespace NonCopyable_

typedef NonCopyable_::NonCopyable NonCopyable;

} // namespace util

} // namespace unity

#endif
