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

#ifndef UNITY_UTIL_FILEIO_H
#define UNITY_UTIL_FILEIO_H

#include <unity/SymbolExport.h>

#include <string>
#include <vector>

namespace unity
{

namespace util
{

UNITY_API std::string read_text_file(std::string const& filename);
UNITY_API std::vector<uint8_t> read_binary_file(std::string const& filename);

} // namespace util

} // namespace unity

#endif
