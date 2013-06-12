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

#ifndef UNITY_INTERNAL_EXCEPTIONIMPL_H
#define UNITY_INTERNAL_EXCEPTIONIMPL_H

#include <unity/util/NonCopyable.h>

#include <string>
#include <exception>

namespace unity
{

class Exception;

namespace internal
{

class ExceptionImpl : private util::NonCopyable
{
public:
    explicit ExceptionImpl(std::string const& reason);

    virtual char const* what() const noexcept = 0;
    virtual std::string reason() const;
    virtual std::string to_string(std::nested_exception const& nested, int indent_level, std::string const& indent) const;

    std::exception_ptr remember(unity::Exception const* env, std::exception_ptr earlier_exception);
    std::exception_ptr remember(unity::Exception const* env, Exception const& earlier_exception);
    std::exception_ptr get_earlier() const noexcept;

protected:
    virtual ~ExceptionImpl() noexcept;

private:
    std::string const reason_;
    std::exception_ptr previous_;
};

} // namespace internal

} // namespace unity

#endif
