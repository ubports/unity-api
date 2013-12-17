/*
 * Copyright (C) 2012 Canonical Ltd
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

#include <unity/UnityExceptions.h>

using namespace std;

namespace unity
{

InvalidArgumentException::InvalidArgumentException(string const& reason)
    : Exception("unity::InvalidArgumentException", reason)
{
}

InvalidArgumentException::InvalidArgumentException(InvalidArgumentException const&) = default;

//! @cond

InvalidArgumentException& InvalidArgumentException::operator=(InvalidArgumentException const&) = default;


InvalidArgumentException::~InvalidArgumentException() noexcept = default;

//! @endcond

exception_ptr InvalidArgumentException::self() const
{
    return make_exception_ptr(*this);
}

LogicException::LogicException(string const& reason)
    : Exception("unity::LogicException", reason)
{
}

LogicException::LogicException(LogicException const&) = default;

//! @cond

LogicException& LogicException::operator=(LogicException const&) = default;

LogicException::~LogicException() noexcept = default;

//! @endcond

exception_ptr LogicException::self() const
{
    return make_exception_ptr(*this);
}

ShutdownException::ShutdownException(string const& reason)
    : Exception("unity::ShutdownException", reason)
{
}

ShutdownException::ShutdownException(ShutdownException const&) = default;

//! @cond

ShutdownException& ShutdownException::operator=(ShutdownException const&) = default;

ShutdownException::~ShutdownException() noexcept = default;

//! @endcond

exception_ptr ShutdownException::self() const
{
    return make_exception_ptr(*this);
}

FileException::FileException(string const& reason, int err)
    : Exception("unity::FileException", reason + (reason.empty() ? "" : " ") + "(errno = " + std::to_string(err) + ")")
    , err_(err)
{
}

FileException::FileException(FileException const&) = default;

//! @cond

FileException& FileException::operator=(FileException const&) = default;

FileException::~FileException() noexcept = default;

//! @endcond

int
FileException::error() const noexcept
{
    return err_;
}

exception_ptr FileException::self() const
{
    return make_exception_ptr(*this);
}

SyscallException::SyscallException(string const& reason, int err)
    : Exception("unity::SyscallException", reason + (reason.empty() ? "" : " ") + "(errno = " + std::to_string(err) + ")")
    , err_(err)
{
}

SyscallException::SyscallException(SyscallException const&) = default;

//! @cond

SyscallException& SyscallException::operator=(SyscallException const&) = default;

SyscallException::~SyscallException() noexcept = default;

//! @endcond

int SyscallException::error() const noexcept
{
    return err_;
}

exception_ptr SyscallException::self() const
{
    return make_exception_ptr(*this);
}

ResourceException::ResourceException(string const& reason)
    : Exception("unity::ResourceException", reason)
{
}

ResourceException::ResourceException(ResourceException const&) = default;

//! @cond

ResourceException& ResourceException::operator=(ResourceException const&) = default;

ResourceException::~ResourceException() noexcept = default;

//! @endcond

exception_ptr ResourceException::self() const
{
    return make_exception_ptr(*this);
}

} // namespace unity
