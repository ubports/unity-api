/*
 * Copyright (C) 2012 Canonical Ltd
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

#include <unity/internal/UnityExceptionsImpl.h>

using namespace std;

namespace unity
{

namespace internal
{

InvalidArgumentExceptionImpl::
InvalidArgumentExceptionImpl(string const& reason)
    : ExceptionImpl(reason)
{
}

char const*
InvalidArgumentExceptionImpl::
what() const noexcept
{
    return "unity::InvalidArgumentException";
}

LogicExceptionImpl::
LogicExceptionImpl(string const& reason)
    : ExceptionImpl(reason)
{
}

char const*
LogicExceptionImpl::
what() const noexcept
{
    return "unity::LogicException";
}

ShutdownExceptionImpl::
ShutdownExceptionImpl(string const& reason)
    : ExceptionImpl(reason)
{
}

char const*
ShutdownExceptionImpl::
what() const noexcept
{
    return "unity::ShutdownException";
}

FileExceptionImpl::
FileExceptionImpl(string const& reason, int err)
    : ExceptionImpl(reason + (err == 0 ? "" : " (errno = " + std::to_string(err) + ")"))
    , errno_(err)
{
}

char const*
FileExceptionImpl::
what() const noexcept
{
    return "unity::FileException";
}

int
FileExceptionImpl::
error() const noexcept
{
    return errno_;
}

SyscallExceptionImpl::
SyscallExceptionImpl(string const& reason, int err)
    : ExceptionImpl(reason + (reason.empty() ? "" : " ") + "(errno = " + std::to_string(err) + ")")
    , errno_(err)
{
}

char const*
SyscallExceptionImpl::
what() const noexcept
{
    return "unity::SyscallException";
}

int
SyscallExceptionImpl::
error() const noexcept
{
    return errno_;
}

ResourceExceptionImpl::
ResourceExceptionImpl(string const& reason)
    : ExceptionImpl(reason)
{
}

char const*
ResourceExceptionImpl::
what() const noexcept
{
    return "unity::ResourceException";
}


} // namespace internal

} // namespace unity
