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

#include <unity/util/Daemon.h>
#include <unity/util/internal/DaemonImpl.h>

using namespace std;

namespace unity
{

namespace util
{

Daemon::UPtr
Daemon::
create()
{
    return UPtr(new Daemon());
}

// This is covered by tests, but only when we are not building for coverage.
// (Closing all file descriptors interferes with the coverage reporting.)

// LCOV_EXCL_START

void
Daemon::
close_fds() noexcept
{
    p_->close_fds();
}

// LCOV_EXCL_STOP

void
Daemon::
reset_signals() noexcept
{
    p_->reset_signals();
}

void
Daemon::
set_umask(mode_t mask) noexcept
{
    p_->set_umask(mask);
}

void
Daemon::
set_working_directory(string const& working_directory)
{
    p_->set_working_directory(working_directory);
}

// Turn this process into a proper daemon in its own session and without a control terminal.
// Whether to close open file descriptors, reset signals to their defaults, change the umask,
// or change the working directory is determined by the setters above.

void
Daemon::
daemonize_me()
{
    p_->daemonize_me();
}

Daemon::
Daemon()
    : p_(new internal::DaemonImpl())
{
}

Daemon::
~Daemon() noexcept
{
}

} // namespace util

} // namespace unity
