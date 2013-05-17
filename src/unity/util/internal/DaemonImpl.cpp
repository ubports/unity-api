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

#include <unity/util/internal/DaemonImpl.h>
#include <unity/util/internal/ResourcePtr.h>

#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cassert>
#include <sstream>
#include <vector>

using namespace std;

namespace unity
{

namespace util
{

namespace internal
{

DaemonImpl::
DaemonImpl()
    : close_fds_(false), reset_signals_(false), set_umask_(false)
{
}

void
DaemonImpl::
close_fds() noexcept
{
    close_fds_ = true;
}

void
DaemonImpl::
reset_signals() noexcept
{
    reset_signals_ = true;
}

void
DaemonImpl::
set_umask(mode_t mask) noexcept
{
    set_umask_ = true;
    umask_ = mask;
}

void
DaemonImpl::
set_working_directory(string const& working_directory)
{
    working_directory_ = working_directory;
}

// Turn this process into a proper daemon in its own session and without a control terminal.
// Whether to close open file descriptors, reset signals to their defaults, change the umask,
// or change the working directory is determined by the setters above.

void
DaemonImpl::
daemonize_me()
{
    // Let's start by changing the working directory because that is the most likely thing to fail. If it does
    // fail, we have not modified any other properties of the calling process.
    // We save the current working dir in case we need to restore it if the first fork fails.
    internal::ResourcePtr<int, std::function<void(int)>>
        old_working_dir([](int fd) { if (fd != -1) { fchdir(fd); close(fd); } });

    if (!working_directory_.empty())
    {
        old_working_dir.reset(open(".", 0));                // Doesn't matter if this fails
        if (chdir(working_directory_.c_str()) == -1)
        {
            ostringstream msg;
            msg << "chdir(\"" << working_directory_.c_str() << "\") failed";
            throw SyscallException(msg.str(), errno);
        }
    }

    // Fork and let the parent exit.

    switch (fork())
    {
        case -1:
        {
            // Strong exception guarantee: if working dir was changed, old_working_dir
            // destructor will try to restore it.
            throw SyscallException("fork() failed", errno); // LCOV_EXCL_LINE
        }
        case 0:
        {
            if (old_working_dir.has_resource())
            {
                close(old_working_dir.get());               // Re-claim file descriptor straight away
                old_working_dir.release();                  // Don't restore previous working dir
            }
            break;                                          // Child process
        }
        default:
        {
            exit(EXIT_SUCCESS);                             // Parent process, we are done.
        }
    }

    // Make us a process group leader, thereby losing the control terminal.
    // No error check needed here: the only possible error is EPERM which means we are a process
    // group leader already. But that's impossible because we just forked and are the child.

    setsid();

    // Set the umask if the caller asked for that. No error checking here because umask() cannot fail.

    if (set_umask_)
    {
        umask(umask_);
    }

    // We are about to fork a second time, to prevent the process from re-acquiring a control terminal if it
    // later opens a terminal device. Because we are a session leader now, we need to ignore SIGHUP, otherwise,
    // when the parent exits after the next fork, we'll receive SIGHUP and die. We remember the previous SIGHUP
    // disposition so we can restore it to what it was if the caller doesn't want all signals to be
    // reset to their default behavior.

    struct sigaction old_action;
    memset(&old_action, 0, sizeof(old_action)); // To stop valgrind complaints
    struct sigaction action;
    memset(&action, 0, sizeof(old_action));     // To stop valgrind complaints
    action.sa_handler = SIG_IGN;
    sigaction(SIGHUP, &action, &old_action);

    switch (fork())
    {
        case -1:
        {
            // LCOV_EXCL_START
            sigaction(SIGHUP, &old_action, nullptr);         // Strong exception guarantee
            throw SyscallException("fork() failed", errno);  // Better than trying to muddle on despite the problem.
            // LCOV_EXCL_STOP
        }
        case 0:
        {
            break;                                           // Child process
        }
        default:
        {
            exit(EXIT_SUCCESS);                              // Parent process, we are done.
        }
    }

    // From here on, we do as much of the daemonizing as we can, ignoring errors from system calls.
    // That's because, now that the second fork has happened, we are committed. Any system call errors below
    // are effectively impossible anyway because things like closing open files and changing signal disposition
    // never fail unless the OS is seriously ill.

    if (!reset_signals_ && old_action.sa_handler != action.sa_handler)
    {
        sigaction(SIGHUP, &old_action, nullptr);    // Restore previous disposition for SIGHUP.
    }

    // If the caller asked for it, we reset all signals to the default behavior.

    if (reset_signals_)
    {
        action.sa_handler = SIG_DFL;
        for (int sig = 1; sig < NSIG; ++sig)
        {
            sigaction(sig, &action, nullptr);
        }
    }

    // Close standard descriptors plus, if the caller asked for that, all others, and
    // connect the standard file descriptors to /dev/null.

    close_open_files();

    int fd = open("/dev/null", O_RDWR);
    assert(fd == 0);
    fd = dup(fd);
    assert(fd == 1);
    fd = dup(fd);
    assert(fd == 2);
}

// Close all open file descriptors

void
DaemonImpl::
close_open_files() noexcept
{
    if (close_fds_)
    {
        // Close all open files. We use /proc to figure out what files are open.
        // That's more efficient than calling close() potentially tens of thousands of times, once for each possible
        // descriptor up to the process limit. We close the standard file descriptors as well because we need to
        // re-open those later anyway.

        char const* proc_self_fd = "/proc/self/fd";

        internal::ResourcePtr<DIR*, decltype(&closedir)> dir(opendir(proc_self_fd), closedir);
        if (dir.get() == nullptr)
        {
            return;  // This should never happen but, for diligence, we check anyway. // LCOV_EXCL_LINE
        }

        vector<int> descriptors; // We collect the file descriptors to close here

        // We use the re-entrant version of readdir().

        size_t len = offsetof(struct dirent, d_name) + pathconf(proc_self_fd, _PC_NAME_MAX) + 1;
        unique_ptr<struct dirent, decltype(&free)> entry(reinterpret_cast<struct dirent*>(malloc(len)), free);

        struct dirent* result_p;

        readdir_r(dir.get(), entry.get(), &result_p);  // Read first entry

        while (result_p)
        {
            if (result_p->d_name[0] != '.') // Ignore . and ..
            {
                // Try to treat the file name as a number. If it doesn't look like a number, something is seriously
                // wrong because /proc/self/fd is supposed to contain only open file descriptor numbers. Rather than
                // giving up in that case, we keep going, closing as many file descriptors as we can.

                size_t pos;
                int fd = std::stoi(result_p->d_name, &pos);
                if (result_p->d_name[pos] == '\0')              // The file name did parse as a number
                {
                    // We can't call close() here because that would modify the directory while we are iterating
                    // over it, which has undefined behavior.
                    descriptors.push_back(fd);
                }
            }
            readdir_r(dir.get(), entry.get(), &result_p);  // Read next entry
        }

        // Close all open descriptors.

        for (auto fd : descriptors)
        {
            close(fd);
        }
    }
    else
    {
        // Caller asked for file descriptors to be left alone, so we only close the standard three.

        close(0);
        close(1);
        close(2);
    }
}

} // namespace internal

} // namespace util

} // namespace unity
