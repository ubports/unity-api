//
// DO NOT EDIT Version.h (this file)! It is generated from Version.h.cmake.
//

/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

#ifndef UNITY_API_VERSION_H
#define UNITY_API_VERSION_H

#define UNITY_API_VERSION_MAJOR @UNITY_API_MAJOR@
#define UNITY_API_VERSION_MINOR @UNITY_API_MINOR@
#define UNITY_API_VERSION_MICRO @UNITY_API_MICRO@

#define UNITY_API_VERSION_STRING "@UNITY_API_VERSION@"

namespace unity
{

namespace api
{

/**
\brief Class to obtain version information for the Unity API at run time.

Version information is represented as
<i>&lt;<code>major</code>&gt;</i>.<i>&lt;<code>minor</code>&gt;</i>.<i>&lt;<code>micro</code>&gt;</i>.

Releases that differ in the major or minor version number are binary incompatible.

Releases of the library that differ only in the micro version number are binary compatible with older releases,
so client code does not need to be recompiled to use the newer library version.

A different minor version is compatible at the API level, that is, it may add new APIs, but does not change existing
ones. API clients must be recompiled for a new major version.

A different major version indicates incompatible API changes.
*/

// Version could be a namespace instead of a class, but that requires a lower-case name,
// which is inconsistent with the remainder of the API.

class Version
{
public:
    /**
    \brief Returns the major version number of the Unity API library.
    */
    static int major_version();

    /**
    \brief Returns the minor version number of the Unity API library.
    */
    static int minor_version();

    /**
    \brief Returns the micro version number of the Unity API library.
    */
    static int micro_version();

    /**
    \brief Returns the Unity API version as a string in the format
    <i>&lt;<code>major</code>&gt;</i>.<i>&lt;<code>minor</code>&gt;</i>.<i>&lt;<code>micro</code>&gt;</i>.
    */
    static const char* str();    // Returns "major.minor.micro"

    // TODO: Add methods to report compiler version and compiler flags

private:
    Version() = delete;
    ~Version() = delete;
};

} // namespace api

} // namespace unity

#endif
