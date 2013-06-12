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

#ifndef UNITY_INTERNAL_UNITYEXCEPTIONSIMPL_H
#define UNITY_INTERNAL_UNITYEXCEPTIONSIMPL_H

#include <unity/internal/ExceptionImpl.h>

#include <string>
#include <exception>

namespace unity
{

class Exception;

namespace internal
{

class InvalidArgumentExceptionImpl : public ExceptionImpl
{
public:
    InvalidArgumentExceptionImpl(std::string const& reason);

    virtual char const* what() const noexcept override;
};

class LogicExceptionImpl : public ExceptionImpl
{
public:
    LogicExceptionImpl(std::string const& reason);

    virtual char const* what() const noexcept override;
};

class ShutdownExceptionImpl : public ExceptionImpl
{
public:
    ShutdownExceptionImpl(std::string const& reason);

    virtual char const* what() const noexcept override;
};

class FileExceptionImpl : public ExceptionImpl
{
public:
    FileExceptionImpl(std::string const& reason, int err);

    virtual char const* what() const noexcept override;
    int error() const noexcept;

private:
    int errno_;
};

class SyscallExceptionImpl : public ExceptionImpl
{
public:
    SyscallExceptionImpl(std::string const& reason, int err);

    virtual char const* what() const noexcept override;
    int error() const noexcept;

private:
    int const errno_;
};

class ResourceExceptionImpl : public ExceptionImpl
{
public:
    ResourceExceptionImpl(std::string const& reason);

    virtual char const* what() const noexcept override;
};

} // namespace internal

} // namespace unity

#endif
