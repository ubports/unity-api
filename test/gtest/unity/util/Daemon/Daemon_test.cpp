/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

#include <unity/util/Daemon.h>
#include <unity/UnityExceptions.h>

#include <fcntl.h>
#include <sys/param.h>
#include <gtest/gtest.h>

using namespace std;
using namespace unity;
using namespace unity::util;

//
// The daemonize_me() method forks and lets the parent exit with zero exit status. In addition, it connects
// the standard file descriptors to /dev/null. This means we cannot use gtest EXPECT macros to test because,
// as far as gtest is concerned, everything worked just fine.
//
// To deal with this, we create a file Daemon_test.out in the directory the test runs in. If the file is
// empty after the test, we know that the test succeeded. Otherwise, it contains messages
// for any failure that were detected.
//

char const* error_file = "Daemon_test.out";

int
clear_error_file()
{
    mode_t old_umask = umask(0);   // Make sure we have mode rw-rw-rw for the file, otherwise different
                                   // people running the test can have problems.
    int fd = open(error_file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    umask(old_umask);
    close(fd);
    return fd;
}

// Write the supplied message into the error file, preceded by file name and line number.
// We open and close the file for each new line because daemonize_me() may close file descriptors,
// so we cannot keep the error file open while the various tests are running. We use a raw write() system
// call to write the messages, so there are no buffering issues, even if we crash unexpectedly.

void
error(string const& file, int line, string const& msg)
{
    int fd = open(error_file, O_APPEND | O_WRONLY);
    if (fd == -1)
    {
        // Little we can do here, seeing that we are a daemon.
        abort();
    }
    ostringstream s;
    s << file << ":" << line;
    if (!msg.empty())
    {
        s << ": " << msg;
    }
    s << endl;
    string l = s.str();
    int bytes __attribute__((unused))
        = write(fd, l.c_str(), l.size()); // Need to use return value to stop warning from gcc.
    close(fd);
}

// Check that the standard three file descriptors are connected to /dev/null.

void
check_std_descriptors()
{
    struct stat null_st;
    if (stat("/dev/null", &null_st) == -1)
    {
        error(__FILE__, __LINE__, "stat() failed");
    }

    struct stat st;

    if (fstat(0, &st) == -1)
    {
        error(__FILE__, __LINE__, "fstat() failed");
    }
    if (st.st_dev != null_st.st_dev || st.st_ino != null_st.st_ino)
    {
        error(__FILE__, __LINE__, "stdin not opened to /dev/null");
    }

    if (fstat(1, &st) == -1)
    {
        error(__FILE__, __LINE__, "fstat() failed");
    }
    if (st.st_dev != null_st.st_dev || st.st_ino != null_st.st_ino)
    {
        error(__FILE__, __LINE__, "stdout not opened to /dev/null");
    }

    if (fstat(2, &st) == -1)
    {
        error(__FILE__, __LINE__, "fstat() failed");
    }
    if (st.st_dev != null_st.st_dev || st.st_ino != null_st.st_ino)
    {
        error(__FILE__, __LINE__, "stderr not opened to /dev/null");
    }
}

// Check if fd is a descriptor for an open file.

bool
is_open(int fd)
{
    struct stat st;
    return fstat(fd, &st) != -1;
}

string
get_cwd()
{
    char* wd = get_current_dir_name();
    if (wd == nullptr)
    {
        abort();
    }
    string dir = wd;
    free(wd);
    return dir;
}

TEST(Daemon, basic)
{
    // Clear the error file. We do this only once, for this first test, so we start out with an empty file.
    // Any test failures reported hereafter append to the file.

    if (clear_error_file() == -1)
    {
        cerr << "Daemon_test.cpp: cannot clear error file" << endl;
        abort();
    }

    Daemon::UPtr d = Daemon::create();

    int pid = getpid();

    // Open a file so we can check that the file is still open after daemonizing.

    int fd = open(".", O_RDONLY);
    if (fd == -1)
    {
        abort();
    }

    d->daemonize_me();
    EXPECT_TRUE(pid != getpid());   // We really did fork...

    check_std_descriptors();

    if (!is_open(fd))
    {
        error(__FILE__, __LINE__, "test file closed, should be open");
    }

    close(fd);
}

// Dummy signal handler

void
hup_handler(int)
{
}

TEST(Daemon, signals)
{
    // Check that signal mask is changed or left alone as appropriate.

    Daemon::UPtr d = Daemon::create();

    // Set SIGUSR1 to be ignored and set SIGHUP to be caught.

    struct sigaction usr1_action;
    memset(&usr1_action, 0, sizeof(usr1_action));           // To stop valgrind complaints
    usr1_action.sa_handler = SIG_IGN;
    if (sigaction(SIGUSR1, &usr1_action, nullptr) == -1)
    {
        error(__FILE__, __LINE__, "cannot ignore SIGUSR1");
        abort();
    }

    struct sigaction hup_action;
    memset(&hup_action, 0, sizeof(hup_action));           // To stop valgrind complaints
    hup_action.sa_handler = hup_handler;
    if (sigaction(SIGHUP, &hup_action, nullptr) == -1)
    {
        error(__FILE__, __LINE__, "cannot catch SIGHUP");
        abort();
    }

    d->daemonize_me();

    struct sigaction prev_action;

    if (sigaction(SIGUSR1, &usr1_action, &prev_action) == -1)
    {
        error(__FILE__, __LINE__, "cannot restore SIGUSR1");
        abort();
    }
    if (prev_action.sa_handler != usr1_action.sa_handler)
    {
        error(__FILE__, __LINE__, "SIGUSR1 should have been left alone, but wasn't");
    }

    if (sigaction(SIGHUP, &hup_action, &prev_action) == -1)
    {
        error(__FILE__, __LINE__, "cannot restore SIGHUP");
        abort();
    }
    if (prev_action.sa_handler != hup_action.sa_handler)
    {
        error(__FILE__, __LINE__, "SIGHUP should have been left alone, but wasn't");
    }

    // Daemonize again, resetting signals, so we can check that they are at the defaults.

    d->reset_signals();
    d->daemonize_me();

    if (sigaction(SIGUSR1, &usr1_action, &prev_action) == -1)
    {
        error(__FILE__, __LINE__, "cannot set SIGUSR1");
        abort();
    }
    if (prev_action.sa_handler != SIG_DFL)
    {
        error(__FILE__, __LINE__, "SIGUSR1 should have been reset, but wasn't");
    }

    if (sigaction(SIGHUP, &hup_action, &prev_action) == -1)
    {
        error(__FILE__, __LINE__, "cannot set SIGHUP");
        abort();
    }
    if (prev_action.sa_handler != SIG_DFL)
    {
        error(__FILE__, __LINE__, "SIGHUP should have been reset, but wasn't");
    }
}

TEST(Daemon, umask)
{
    // Check that umask is changed or left alone as appropriate.

    Daemon::UPtr d = Daemon::create();

    umask(027);
    d->daemonize_me();
    mode_t new_umask = umask(022);
    if (new_umask != 027)
    {
        error(__FILE__, __LINE__, "umask was changed, but should not have been");
    }

    // Daemonize again, changing umask, so we can check that the umask was indeed changed.

    d->set_umask(0);
    d->daemonize_me();
    new_umask = umask(027);
    if (new_umask != 0)
    {
        error(__FILE__, __LINE__, "umask was not changed, but should have been");
    }
}

TEST(Daemon, dir)
{
    // Check that working directory is changed or left alone as appropriate.

    Daemon::UPtr d = Daemon::create();

    string old_wd = get_cwd();
    d->daemonize_me();
    string new_wd = get_cwd();
    if (new_wd != old_wd)
    {
        error(__FILE__, __LINE__, "working dir was changed, but should not have been");
    }

    // Daemonize again, changing directory, so we can check that the directory was indeed changed.

    d->set_working_directory("/");
    d->daemonize_me();
    new_wd = get_cwd();

    if (new_wd != "/")
    {
        error(__FILE__, __LINE__, "working dir was not changed, but should have been");
    }

    // Check that errors in setting working directory are correctly diagnosed.

    d->set_working_directory("/no_such_directory");
    try
    {
        d->daemonize_me();
        error(__FILE__, __LINE__, "daemonize_me() should have thrown, but didn't");

        FAIL();
    }
    catch (SyscallException const& e)
    {
        if (e.to_string() != "unity::SyscallException: chdir(\"/no_such_directory\") failed (errno = 2)")
        {
            error(__FILE__, __LINE__, "wrong message for SyscallException");
        }
    }
}

TEST(Daemon, tty)
{
    // Check that the process cannot re-acquire a control terminal

    Daemon::UPtr d = Daemon::create();

    d->daemonize_me();

    int fd = open("/dev/tty", O_RDWR);
    if (fd != -1)
    {
        error(__FILE__, __LINE__, "re-acquired control terminal but should not have been able to");
    }
}

// Test that file descriptors are closed.
// We test this only when coverage is disabled because
// closing descriptors interferes with coverage reporting.

#if !defined(COVERAGE_ENABLED)

TEST(Daemon, file_close)
{
    Daemon::UPtr d = Daemon::create();

    // Open a file so we can check that the file is closed after daemonizing.

    int fd = open(".", O_RDONLY);
    if (fd == -1)
    {
        abort();
    }

    int fd2 = open(".", O_RDONLY);
    if (fd2 == -1)
    {
        abort();
    }

    d->close_fds();
    d->daemonize_me();
    check_std_descriptors();

    if (is_open(fd))
    {
        error(__FILE__, __LINE__, "fd open, should be closed");
    }
    if (is_open(fd2))
    {
        error(__FILE__, __LINE__, "fd2 open, should be closed");
    }
}

#endif
