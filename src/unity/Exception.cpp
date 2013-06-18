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

#include <unity/Exception.h>
#include <unity/ExceptionImplBase.h>

using namespace std;

namespace unity
{

//! @cond

Exception::Exception(shared_ptr<ExceptionImplBase> const& derived)
    : p_(derived)
{
}

Exception::Exception(Exception const&) = default;

Exception& Exception::operator=(Exception const&) = default;

Exception::~Exception() noexcept = default;

//! @endcond

/**
\brief Returns the reason set by the derived class's constructor (empty string if none).

Derived classes should include any other state information, such as the value of data members or
other relevant detail in the <code>reason</code> string they pass to the protected constructor.
*/

string Exception::reason() const
{
    return p_->reason();
}

/**
\brief Returns a string describing the exception, including any exceptions that were nested or chained.

Nested exceptions are indented according to their nesting level. If the exception contains chained
exceptions, these are shown in oldest-to-newest order.

\param indent This controls the amount of indenting per level. The default indent is four spaces.
\return The string describing the exception.

\note The default implementation of this member function calls <code>to_string(0, indent)</code>.
*/

string Exception::to_string(std::string const& indent) const
{
    return p_->to_string(this, 0, indent);
}

/**
\brief Returns a string describing the exception, including any exceptions that were nested or chained.

Nested exceptions are indented according to their nesting level. If the exception contains chained
exceptions, these are shown in oldest-to-newest order.

\param indent_level This controls the indent level. The value <code>0</code> indicates
       the outermost level (no indent).
\param indent This controls the amount of indenting per level. The passed string is prependended
       <i><code>indent_level</code></i> times to each line.
\return The string describing the exception.

\note This member function has a default implementation, so derived classes do not need to override it
      unless they want to change the formatting of the returned string.
*/

string Exception::to_string(int indent_level, std::string const& indent) const
{
    return p_->to_string(this, indent_level, indent);
}

/**
\brief Adds an exception to the exception history chain.

\param earlier_exception The parameter must be a <code>nullptr</code> or a <code>std::exception_ptr</code>
to an exception that was remembered earlier. This allows a sequence of exceptions to be remembered without
having to throw them and is useful for example, in shutdown scenarios where any one of a sequence of steps
can fail, but we want to continue and try all the following steps and only throw after all of them have been
tried. In this case, each step that fails can add itself to the sequence of remembered exceptions, and finally
throw something like <code>ShutdownException</code>.
\return A <code>std::exception_ptr</code> to <code>this</code>.
*/

exception_ptr Exception::remember(exception_ptr earlier_exception)
{
    return p_->set_earlier(earlier_exception);
}

/**
\brief Returns the previous exception.
\return Returns the next-older remembered exception, or <code>nullptr</code>, if none.
*/

exception_ptr Exception::get_earlier() const noexcept
{
    return p_->get_earlier();
}

/**
\brief Returns a pointer to to the implementation instance.
*/

ExceptionImplBase* Exception::pimpl() const noexcept
{
    return p_.get();
}

} // namespace unity
