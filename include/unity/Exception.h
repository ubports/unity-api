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

#ifndef UNITY_EXCEPTION_H
#define UNITY_EXCEPTION_H

#include <unity/config.h>

#include <exception>
#include <string>
#include <memory>

namespace unity
{

namespace internal
{
class ExceptionImpl;
}

// TODO: It probably would be best to split this into a base and ImplBase, with the derived part in the internal
//       namespace and declaring self(), the constructor, and pimpl(). That's because the Impl for the exception
//       is in the internal namespace, so public API clients can use Exception instances, but they cannot
//       create new derived exceptions because the Impl classes are internal to Unity.

/**
\brief Abstract base class for all Unity exceptions.

This class is the base class for all Unity exceptions. Besides providing a common base class for
structured exception handling, this class provides features to capture nested exceptions (for
exceptions that are re-thrown) and to chain exceptions into an exception history that allows
a number of exceptions to be remembered before throwing a new exception.

The exception nesting is provided by the derivation from <code>std::nested_exception</code>. If you
catch an exception and throw another exception from the catch handler, the caught exception
is automatically preserved; you can access nested exceptions by calling the <code>nested_ptr()</code> and
<code>rethrow_nested()</code> member functions of <code>std::nested_exception</code>.

In addition, you can remember one or more exceptions by calling remember(). This is useful in situations
where you need perform a number of actions that may fail with an error code, and you do not want to
throw an exception until all of the actions have been attempted. This is particularly useful in shutdown
scenarios, where it is often impossible to recover from an error, but it is still desirable to try to
shut down as much as possible before reporting or logging the errors:

~~~
void
shutdown()
{
    using namespace std;

    exception_ptr ep;

    try
    {
        shutdown_action_1();
    }
    catch (SomeException const&)
    {
        ep = make_exception_ptr(current_exception());
    }

    try
    {
        shutdown_action_2();
    }
    catch (SomeOtherException const&)
    {
        ep = e.remember(ep);
    }

    int err = shutdown_action_3();
    if (err != 0)
    {
        try
        {
            throw YetAnotherException(err);
        }
        catch (YetAnotherException const& e)
        {
            ep = e.remember(ep);
        }
    }

    if (ep)
    {
        rethrow_exception(ep);
    }
}
~~~

Calling to_string() on a caught exception returns a string with the entire exception history (both nested and
chained).

*/

class UNITY_API Exception : public std::exception, public std::nested_exception
{
public:
    //! @cond
    Exception(Exception const&);
    Exception& operator=(Exception const&);
    virtual ~Exception() noexcept;
    //! @endcond

    /**
    \brief Returns the name of the exception.

    Derived classes must override what() to return <i>only</i> the (fully-qualified) name of the derived
    exception. If the derived class sets a reason string (or contains other details), it should <i>not</i>
    include the reason or details as part of the string return returned by what().
    */
    virtual char const* what() const noexcept = 0;

    virtual std::string reason() const;

    virtual std::string to_string(std::string const& indent = "    ") const;
    virtual std::string to_string(int indent_level, std::string const& indent) const;

    std::exception_ptr remember(std::exception_ptr earlier_exception);
    std::exception_ptr get_earlier() const noexcept;

    /**
    \brief Returns a <code>std::exception_ptr</code> to <code>this</code>.

    \note Derived exceptions must implement this member function so the implemention of remember()
    (provided by this abstract base class) can return a <code>std::exception_ptr</code> to its own derived exception.
    */
    virtual std::exception_ptr self() const = 0;

protected:
    //! @cond
    Exception(std::shared_ptr<internal::ExceptionImpl> const& derived);
    internal::ExceptionImpl* pimpl() const noexcept;     // No need to reimplement in derived
    //! @endcond

private:
    std::shared_ptr<internal::ExceptionImpl> p_;         // shared_ptr instead of unique_ptr because
                                                         // exceptions must be copyable
};

} // namespace unity

#endif
