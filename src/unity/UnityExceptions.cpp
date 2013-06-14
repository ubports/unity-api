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

#include <unity/UnityExceptions.h>
#include <unity/internal/UnityExceptionsImpl.h>

using namespace std;

namespace unity
{

InvalidArgumentException::
InvalidArgumentException(string const& reason)
    : Exception(make_shared<internal::InvalidArgumentExceptionImpl>(reason))
{
}

InvalidArgumentException::
InvalidArgumentException(InvalidArgumentException const&) = default;

//! @cond

InvalidArgumentException&
InvalidArgumentException::
operator=(InvalidArgumentException const&) = default;


InvalidArgumentException::
~InvalidArgumentException() noexcept = default;

//! @endcond

char const*
InvalidArgumentException::
what() const noexcept
{
    return dynamic_cast<internal::InvalidArgumentExceptionImpl*>(pimpl())->what();
}

exception_ptr
InvalidArgumentException::
self() const
{
    return make_exception_ptr(*this);
}

LogicException::
LogicException(string const& reason)
    : Exception(make_shared<internal::LogicExceptionImpl>(reason))
{
}

LogicException::
LogicException(LogicException const&) = default;

//! @cond

LogicException&
LogicException::
operator=(LogicException const&) = default;

LogicException::
~LogicException() noexcept = default;

//! @endcond

char const*
LogicException::
what() const noexcept
{
    return dynamic_cast<internal::LogicExceptionImpl*>(pimpl())->what();
}

exception_ptr
LogicException::
self() const
{
    return make_exception_ptr(*this);
}

ShutdownException::
ShutdownException(string const& reason)
    : Exception(make_shared<internal::ShutdownExceptionImpl>(reason))
{
}

ShutdownException::
ShutdownException(ShutdownException const&) = default;

//! @cond

ShutdownException&
ShutdownException::
operator=(ShutdownException const&) = default;

ShutdownException::
~ShutdownException() noexcept = default;

//! @endcond

char const*
ShutdownException::
what() const noexcept
{
    return dynamic_cast<internal::ShutdownExceptionImpl*>(pimpl())->what();
}

exception_ptr
ShutdownException::
self() const
{
    return make_exception_ptr(*this);
}

FileException::
FileException(string const& reason, int err)
    : Exception(make_shared<internal::FileExceptionImpl>(reason, err))
{
}

FileException::
FileException(FileException const&) = default;

//! @cond

FileException&
FileException::
operator=(FileException const&) = default;

FileException::
~FileException() noexcept = default;

//! @endcond

char const*
FileException::
what() const noexcept
{
    return dynamic_cast<internal::FileExceptionImpl*>(pimpl())->what();
}

int
FileException::
error() const noexcept
{
    return dynamic_cast<internal::FileExceptionImpl*>(pimpl())->error();
}

exception_ptr
FileException::
self() const
{
    return make_exception_ptr(*this);
}

SyscallException::
SyscallException(string const& reason, int err)
    : Exception(make_shared<internal::SyscallExceptionImpl>(reason, err))
{
}

SyscallException::
SyscallException(SyscallException const&) = default;

//! @cond

SyscallException&
SyscallException::
operator=(SyscallException const&) = default;

SyscallException::
~SyscallException() noexcept = default;

//! @endcond

char const*
SyscallException::
what() const noexcept
{
    return dynamic_cast<internal::SyscallExceptionImpl*>(pimpl())->what();
}

int
SyscallException::
error() const noexcept
{
    return dynamic_cast<internal::SyscallExceptionImpl*>(pimpl())->error();
}

exception_ptr
SyscallException::
self() const
{
    return make_exception_ptr(*this);
}

ResourceException::
ResourceException(string const& reason)
    : Exception(make_shared<internal::ResourceExceptionImpl>(reason))
{
}

ResourceException::
ResourceException(ResourceException const&) = default;

//! @cond

ResourceException&
ResourceException::
operator=(ResourceException const&) = default;

ResourceException::
~ResourceException() noexcept = default;

//! @endcond

char const*
ResourceException::
what() const noexcept
{
    return dynamic_cast<internal::ResourceExceptionImpl*>(pimpl())->what();
}

exception_ptr
ResourceException::
self() const
{
    return make_exception_ptr(*this);
}

} // namespace unity
