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

#include <unity/api/Version.h>

using namespace std;

namespace unity
{

namespace api
{

int
Version::
major_version()
{
    return UNITY_API_VERSION_MAJOR;
}

int
Version::
minor_version()
{
    return UNITY_API_VERSION_MINOR;
}

int
Version::
micro_version()
{
    return UNITY_API_VERSION_MICRO;
}

char const*
Version::
str()
{
    return UNITY_API_VERSION_STRING;
}

} // namespace api

} // namespace unity
