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
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

#include <unity/util/FileIO.h>
#include <unity/util/ResourcePtr.h>
#include <unity/UnityExceptions.h>

#include <sstream>

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;

namespace unity
{

namespace util
{

namespace
{

//
// It would be nice to use fstream for I/O, but the error reporting is so useless that it's better to step
// down to system calls. At least then, when something goes wrong, we know what it was.
//

template<typename T>
vector<T> read_file(string const& filename)
{
    util::ResourcePtr<int, std::function<void(int)>> fd(::open(filename.c_str(), O_RDONLY),
                                                        [](int fd) { if (fd != -1) ::close(fd); });
    if (fd.get() == -1)
    {
        throw FileException("cannot open \"" + filename + "\": " + strerror(errno), errno);
    }

    struct stat st;
    if (fstat(fd.get(), &st) == -1)
    {
        throw FileException("cannot fstat \"" + filename + "\": " + strerror(errno), errno); // LCOV_EXCL_LINE
    }

    if (!S_ISREG(st.st_mode))
    {
        throw FileException("\"" + filename + "\" is not a regular file", 0);
    }

    vector<T> buf(st.st_size);

    if (st.st_size == 0)
    {
        return buf;
    }

    if (read(fd.get(), &buf[0], st.st_size) != st.st_size)
    {
        // LCOV_EXCL_START
        ostringstream msg;
        msg << "cannot read " << st.st_size << " byte";
        if (st.st_size != 1)
        {
            msg << "s";
        }
        msg << " from \"" << filename << "\": " << strerror(errno);
        throw FileException(msg.str(), errno);
        // LCOV_EXCL_STOP
    }

    return buf;
}

} // namespace

string
read_text_file(string const& filename)
{
    vector<char> buf(read_file<char>(filename));
    return string(buf.begin(), buf.end());
}

vector<uint8_t>
read_binary_file(string const& filename)
{
    return read_file<uint8_t>(filename);
}

} // namespace util

} // namespace unity
