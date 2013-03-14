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

#include <gtest/gtest.h>

using namespace unity::api;

TEST(Version, basic)
{
    EXPECT_EQ(Version::major_version(), UNITY_API_VERSION_MAJOR);
    EXPECT_EQ(Version::minor_version(), UNITY_API_VERSION_MINOR);
    EXPECT_EQ(Version::micro_version(), UNITY_API_VERSION_MICRO);
    EXPECT_STREQ(Version::str(), UNITY_API_VERSION_STRING);
}
