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
 * Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>
 */

#ifndef UNITY_UTIL_INIPARSER_H
#define UNITY_UTIL_INIPARSER_H

#include <unity/SymbolExport.h>
#include <unity/util/DefinesPtrs.h>

#include <string>
#include <vector>

namespace unity
{

namespace util
{

namespace internal
{
struct IniParserPrivate;
}

/**
\brief Helper class to read and write configuration files.

This class reads configuration files in the .ini format
and provides for a simple and type safe way of extracting
and inserting information. A typical ini file looks like this:

~~~
[group1]

key1 = value1
key2 = value2

[group2]

key1 = othervalue1
key2 = othervalue2
~~~

To extract/insert a value, simply specify the group and key
names to the get/set methods of this class, respectively.
The array methods use a semicolon as a separator.

To write unsaved changes back to the configuration file, call
sync(). The sync() method will throw a FileException if it
fails to write to file.

The get methods indicate errors by throwing LogicException.

All methods are thread-safe.
*/

class UNITY_API IniParser final {
public:
    /** Parse the given file. */
    IniParser(const char* filename);
    ~IniParser() noexcept;

    /// @cond
    UNITY_DEFINES_PTRS(IniParser);

    IniParser(const IniParser& ip) = delete;
    IniParser() = delete;
    /// @endcond

    //{@

    /** @name Read Methods
     * These member functions provide read access to configuration entries by group and key.<br>
     * Attempts to retrieve a value as the wrong type (such as retrieving a string value as an
     * integer) or to retrieve a value for a non-existent group or key throw LogicException.
     **/

    bool has_group(const std::string& group) const noexcept;
    bool has_key(const std::string& group, const std::string& key) const;

    std::string get_string(const std::string& group, const std::string& key) const;
    std::string get_locale_string(const std::string& group,
                                  const std::string& key,
                                  const std::string& locale = std::string()) const;
    bool get_boolean(const std::string& group, const std::string& key) const;
    int get_int(const std::string& group, const std::string& key) const;
    double get_double(const std::string& group, const std::string& key) const;

    std::vector<std::string> get_string_array(const std::string& group, const std::string& key) const;
    std::vector<std::string> get_locale_string_array(const std::string& group,
                                                     const std::string& key,
                                                     const std::string& locale = std::string()) const;
    std::vector<bool> get_boolean_array(const std::string& group, const std::string& key) const;
    std::vector<int> get_int_array(const std::string& group, const std::string& key) const;
    std::vector<double> get_double_array(const std::string& group, const std::string& key) const;

    std::string get_start_group() const;
    std::vector<std::string> get_groups() const;
    std::vector<std::string> get_keys(const std::string& group) const;

    /** @name Write Methods
     * These member functions provide write access to configuration entries by group and key.<br>
     * Attempts to remove groups or keys that do not exist throw LogicException.<br>
     * The set methods replace the value for a key if the key exists. Calling a set method for a
     * non-existent group and/or key creates the group and/or key.
      **/

    bool remove_group(const std::string& group);
    bool remove_key(const std::string& group, const std::string& key);

    void set_string(const std::string& group, const std::string& key, const std::string& value);
    void set_locale_string(const std::string& group,
                           const std::string& key,
                           const std::string& value,
                           const std::string& locale = std::string());
    void set_boolean(const std::string& group, const std::string& key, bool value);
    void set_int(const std::string& group, const std::string& key, int value);
    void set_double(const std::string& group, const std::string& key, double value);

    void set_string_array(const std::string& group, const std::string& key, const std::vector<std::string>& value);
    void set_locale_string_array(const std::string& group,
                                 const std::string& key,
                                 const std::vector<std::string>& value,
                                 const std::string& locale = std::string());
    void set_boolean_array(const std::string& group, const std::string& key, const std::vector<bool>& value);
    void set_int_array(const std::string& group, const std::string& key, const std::vector<int>& value);
    void set_double_array(const std::string& group, const std::string& key, const std::vector<double>& value);

    /** @name Sync Method
     * This member function writes unsaved changes back to the configuration file.<br>
     * A failure to write to the file throws a FileException.
      **/

    void sync();

    //@}

private:
    internal::IniParserPrivate* p;
};


} // namespace util

} // namespace unity

#endif
