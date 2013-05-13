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

#include <unity/UnityExceptions.h>
#include <unity/util/FileIO.h>

#include <gtest/gtest.h>

#include <fstream>

using namespace std;
using namespace unity;
using namespace unity::util;

TEST(FileIO, basic)
{
    int i __attribute__((unused))
        = system("rm -f testfile; echo \"some chars\" >testfile");

    string s = read_text_file("testfile");
    EXPECT_EQ("some chars\n", s);

    vector<uint8_t> v = read_binary_file("testfile");
    string contents("some chars\n");
    EXPECT_EQ(vector<uint8_t>(contents.begin(), contents.end()), v);

    system("rm -fr empty; >empty");
    s = read_text_file("empty");
    EXPECT_TRUE(s.empty());
}

TEST(FileIO, exceptions)
{
    try
    {
        read_text_file("no_such_file");
        FAIL();
    }
    catch (FileException const& e)
    {
        EXPECT_EQ("unity::FileException: cannot open \"no_such_file\": No such file or directory (errno = 2)",
                  e.to_string());
    }

    try
    {
        int i __attribute__((unused))
            = system("rm -fr testdir; mkdir testdir");
        read_text_file("testdir");
        FAIL();
    }
    catch (FileException const& e)
    {
        EXPECT_EQ("unity::FileException: \"testdir\" is not a regular file", e.to_string());
    }
}
