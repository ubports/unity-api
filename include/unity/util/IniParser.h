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
 * Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>
 */

#ifndef UNITY_UTIL_INIPARSER_H
#define UNITY_UTIL_INIPARSER_H

#include <unity/config.h>

#include<string>
#include<vector>

namespace unity
{

namespace util
{

namespace internal
{
struct IniParserPrivate;
}

/**
\brief Helper class to read configuration files.

This class reads configuration files in the .ini format
and provides for a simple and type safe way of extracting
information. A typical ini file looks like this:

~~~
[group1]

key1 = value1
key2 = value2

[group2]

key1 = othervalue1
key2 = othervalue2
~~~

To obtain a value, simply specify the group and key names to
the get* functions of this class. The array functions use
a semicolon as a separator.

The get functions indicate errors by throwing LogicExceptions.
Examples why this might happen is because a value can't be
coerced into the given type (i.e trying to convert the value
"hello" into a boolean).
*/

class UNITY_API IniParser final {
public:
    /** Create new IniParser. From a file. */
    IniParser(const char *filename);
    ~IniParser() noexcept;

    /** Doxygen is too stupid to realize that this function does not exist. */
    IniParser(const IniParser &ip) = delete;
    IniParser() = delete;

    /** Has group? */
    bool has_group(const std::string &group) const noexcept;
    /** Has key? */
    bool has_key(const std::string &group, const std::string &key) const;
    /** Get string value. */
    std::string get_string(const std::string &group, const std::string &key) const;
    /** Get boolean value. */
    bool get_boolean(const std::string &group, const std::string &key) const;
    /** Get integer value. */
    int get_int(const std::string &group, const std::string &key) const;

    /** Get an array of strings. */
    std::vector<std::string> get_string_array(const std::string &group, const std::string &key) const;
    /** Get an array of integers. */
    std::vector<int> get_int_array(const std::string &group, const std::string &key) const;
    /** Get an array of booleans. */
    std::vector<bool> get_boolean_array(const std::string &group, const std::string &key) const;

    /** Get start group. */
    std::string get_start_group() const;
    /** Get list of groups. */
    std::vector<std::string> get_groups() const;
    /** Get list of keys in a group. */
    std::vector<std::string> get_keys(const std::string &group) const;

private:
    internal::IniParserPrivate *p;
};


} // namespace util

} // namespace unity

#endif
