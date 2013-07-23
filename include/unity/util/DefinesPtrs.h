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

#ifndef UNITY_UTIL_DEFINESPTRS_H
#define UNITY_UTIL_DEFINESPTRS_H

#include <memory>

/**
\file DefinesPtrs.h
\def UNITY_DEFINES_PTRS(classname)
\brief Macro to add smart pointer definitions to a class.

This macro injects type definitions for smart pointer types into a class. It is useful to
establish a common naming convention for smart pointers across a project.

You can use the macro as follows. Note that the macro argument is the name of the class being defined.

~~~
* class MyClass
* {
* public:
*     UNITY_DEFINES_PTRS(MyClass);
*     // MyClass now provides public typedefs for SPtr, SCPtr, UPtr, and UCPtr.
*     // ...
* };
~~~

Callers of <code>MyClass</code> can now, for example, write

~~~
* MyClass::UPtr p(new MyClass);
~~~

*/

#define UNITY_DEFINES_PTRS(classname)               \
    typedef std::shared_ptr<classname>       SPtr;  \
    typedef std::shared_ptr<classname const> SCPtr; \
    typedef std::unique_ptr<classname>       UPtr;  \
    typedef std::unique_ptr<classname const> UCPtr

#endif
