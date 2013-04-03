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

#ifndef UNITY_UTIL_DAEMON_H
#define UNITY_UTIL_DAEMON_H

#include <unity/util/DefinesPtrs.h>
#include <unity/util/NonCopyable.h>

#include <sys/types.h>

namespace unity
{

namespace util
{

namespace internal
{
class DaemonImpl;
}

/**
\class Daemon
\brief Helper class to turn a process into a daemon.

To turn a process into a daemon, instantiate this class and call daemonize_me().

The new process becomes a session leader without a control terminal. The standard
file descriptors (<code>stdin</code>, <code>stdout</code>, and stderr) are closed
and re-opened to <code>/dev/null</code>.

By default, any file descriptors (other than the standard three) that are open in the process
remain open to the same destinations in the daemon. If you want to have other descriptors closed, call
close_fds() before calling daemonize_me(). This will close all file descriptors > 2.

By default, the signal disposition of the daemon is unchanged. To reset all signals to their
default disposition, call reset_signals() before calling daemonize_me().

By default, the umask of the daemon is unchanged. To set a different umask, call set_umask()
before calling daemonize_me().

By default, the working directory of the daemon is unchanged. To run the daemon with a different
working directory, call set_working_dir() before calling daemonize_me(). Note that the working
directory should be set to a path that is in the root file system. If the working directory
is in any other file system, that file system cannot be unmounted while the daemon is running.

Note: This class is not async signal-safe. Do not call daemonize_me() from a a signal handler.
*/

class Daemon final : public util::DefinesPtrs<Daemon>, private NonCopyable
{
public:
    /**
    \brief Create a Daemon instance.
    \return A <code>unique_ptr</code> to the instance.
    */
    static UPtr create();

    /**
    \brief Causes daemonize_me() to close all open file descriptors other than the standard file
           descriptors (which are connected <code>/dev/null</code>).
    */
    void close_fds() noexcept;

    /**
    \brief Causes daemonize_me() to reset all signals to their default behavior.
    */
    void reset_signals() noexcept;

    /**
    \brief Causes daemonize_me() to set the umask.
    \param mask The umask for the daemon process.
    */
    void set_umask(mode_t mask) noexcept;

    /**
    \brief Causes daemonize_me() to set the working directory.
    \param working_directory The working directory for the daemon process.
    \throws SyscallException The process could not change the working directory to the specified directory.
    \note Daemon processes should set their working to "/" or to a directory that is part of the root file system.
          Otherwise, the file system containing the daemon's working directory cannot be unmounted without first
          killing the daemon process.
    */
    void set_working_directory(std::string const& working_directory);

    /**
    \brief Turns the calling process into a daemon.

    By default, daemonize_me() leaves open file descriptors, signal disposition, umask, and working
    directory unchanged. Call the corresponding member function before calling daemonize_me() to
    change this behavior as appropriate.

    \note Calling daemonize_me() more than once is safe; any changes to file descriptors, signal disposition,
    umask, or working directory as requested by calling the other member functions will be correctly set
    for the calling process. However, daemonize_me() is not a cheap call because it calls <code>fork()</code>;
    the normal use pattern is to create a Daemon instance, select the desired settings, call daemonize_me(),
    and let the instance go out of scope.
    */
    void daemonize_me();

    ~Daemon() noexcept;

private:
    Daemon();   // Class is final, instantiation only via create()

    std::unique_ptr<internal::DaemonImpl> p_;
};

} // namespace util

} // namespace unity

#endif
