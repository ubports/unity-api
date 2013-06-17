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

#ifndef UNITY_UTIL_DEFINESPTRS_H
#define UNITY_UTIL_DEFINESPTRS_H

#include <memory>

namespace unity
{

namespace util
{

/**
\brief Helper template to inject smart pointer definitions into a class.

This template injects type definitions for smart pointer types into a class. It is useful to
establish a common naming convention for smart pointers across a project.

You can use the template as follows. Note that the template parameter is the name of the class
being defined ("curiously recurring template pattern").

~~~
* class MyClass : public util::DefinesPtrs<MyClass>
* {
* public:
*     // MyClass now provides public typedefs for SPtr, SCPtr, UPtr, and UCPtr.
*     // ...
* };
~~~

Callers of <code>MyClass</code> can now, for example, write

~~~
* MyClass::UPtr p(new MyClass);
~~~

*/

template <typename T>
class DefinesPtrs
{
public:
    /**
    A <code>std::shared_ptr</code> to a non-constant instance.
    */
    typedef std::shared_ptr<T> SPtr;

    /**
    A <code>std::shared_ptr</code> to a constant instance.
    */
    typedef std::shared_ptr<T const> SCPtr;

    /**
    A <code>std::unique_ptr</code> to a non-constant instance.
    */
    typedef std::unique_ptr<T> UPtr;

    /**
    A <code>std::unique_ptr</code> to a constant instance.
    */
    typedef std::unique_ptr<T const> UCPtr;

protected:                                  // Not meant to be instantiated stand-alone
    DefinesPtrs() = default;
    virtual ~DefinesPtrs() = default;
};

} // namespace util

} // namespace unity

#endif
