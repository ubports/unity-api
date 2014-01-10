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

#ifndef UNITY_UTIL_DAEMONIMPL_H
#define UNITY_UTIL_DAEMONIMPL_H

#include <unity/UnityExceptions.h>
#include <unity/util/NonCopyable.h>

#include <sys/types.h>

#include <string>

namespace unity
{

namespace util
{

namespace internal
{

class DaemonImpl final
{
public:
    NONCOPYABLE(DaemonImpl);

    DaemonImpl();
    ~DaemonImpl() = default;

    void close_fds() noexcept;
    void reset_signals() noexcept;
    void set_umask(mode_t mask) noexcept;
    void set_working_directory(std::string const& working_directory);

    void daemonize_me();

private:
    bool close_fds_;
    bool reset_signals_;
    bool set_umask_;
    mode_t umask_;
    std::string working_directory_;

    void close_open_files() noexcept;
};

} // namespace internal

} // namespace util

} // namespace unity

#endif
