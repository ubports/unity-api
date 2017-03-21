/*
 * Copyright (C) 2016-2017 Canonical Ltd
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
 */

#include "unity/util/SnapPath.h"

namespace unity
{

namespace util
{

std::string prepend_snap_path(const std::string& path)
{
    auto get_snap_path = []() {
        const char* env_snap = getenv("SNAP");
        if (env_snap == nullptr) {
            return "";
        }
        return env_snap;
    };
    return get_snap_path() + path;
}

} // namespace util

} // namespace unity
