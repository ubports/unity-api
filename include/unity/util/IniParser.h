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

#include<string>
#include<vector>

namespace unity
{

namespace util
{

struct IniParserPrivate;

class IniParser final {
public:
    IniParser(const char *filename);
    ~IniParser();

    IniParser(const IniParser &ip) = delete;
    IniParser() = delete;

    bool hasGroup(const std::string &group) const;
    bool hasKey(const std::string &group, const std::string &key) const;
    std::string getString(const std::string &group, const std::string &key) const;
    bool getBoolean(const std::string &group, const std::string &key) const;
    int getInt(const std::string &group, const std::string &key) const;

    std::vector<std::string> getStringArray(const std::string &group, const std::string &key) const;
    std::vector<int> getIntArray(const std::string &group, const std::string &key) const;
    std::vector<bool> getBooleanArray(const std::string &group, const std::string &key) const;

    std::string getStartGroup() const;
    std::vector<std::string> getGroups() const;
    std::vector<std::string> getKeys(const std::string &group) const;

private:
    IniParserPrivate *p;
};


} // namespace util

} // namespace unity

#endif
