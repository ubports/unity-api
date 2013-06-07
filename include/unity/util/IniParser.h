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
the get* functions of this class.

*/

class UNITY_API IniParser final {
public:
    IniParser(const char *filename);
    ~IniParser() noexcept;

    IniParser(const IniParser &ip) = delete;
    IniParser() = delete;

    bool has_group(const std::string &group) const noexcept;
    bool has_key(const std::string &group, const std::string &key) const;
    std::string get_string(const std::string &group, const std::string &key) const;
    bool get_boolean(const std::string &group, const std::string &key) const;
    int get_int(const std::string &group, const std::string &key) const;

    std::vector<std::string> get_string_array(const std::string &group, const std::string &key) const;
    std::vector<int> get_int_array(const std::string &group, const std::string &key) const;
    std::vector<bool> get_boolean_array(const std::string &group, const std::string &key) const;

    std::string get_start_group() const;
    std::vector<std::string> get_groups() const;
    std::vector<std::string> get_keys(const std::string &group) const;

private:
    internal::IniParserPrivate *p;
};


} // namespace util

} // namespace unity

#endif
