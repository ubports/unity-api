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

#ifndef UNITY_EXCEPTIONIMPLBASE_H
#define UNITY_EXCEPTIONIMPLBASE_H

#include <unity/config.h>
#include <unity/util/NonCopyable.h>

#include <exception>
#include <string>
#include <memory>

namespace unity
{

namespace internal
{
class ExceptionData;
}

class Exception;

/**
\brief Implementation base exception class for API clients to derive new pimpl'd exception types from.
\sa unity::Exception
*/

class UNITY_API ExceptionImplBase : public util::NonCopyable
{
public:
    explicit ExceptionImplBase(Exception const* owner, std::string const& reason);
    //! @cond
    virtual ~ExceptionImplBase() noexcept;
    //! @endcond

    std::string reason() const;

    std::string to_string(std::nested_exception const* nested, int indent_level, std::string const& indent) const;

    std::exception_ptr set_earlier(std::exception_ptr earlier_exception);
    std::exception_ptr get_earlier() const noexcept;

private:
    std::shared_ptr<internal::ExceptionData> p_;  // shared_ptr (not unique_ptr) because ExceptionData is incomplete
};

} // namespace unity

#endif
