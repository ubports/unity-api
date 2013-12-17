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

#include <unity/Exception.h>

#include <cassert>

using namespace std;

namespace
{

//
// Return the margin string for the indent level and indent.
//

string get_margin(int indent_level, string const& indent)
{
    string margin;
    for (int i = 0; i < indent_level; ++i)
    {
        margin += indent;
    }
    return margin;
}

//
// Follow the nested exceptions that were rethrown along the call stack, printing them into s.
//

void print_name_and_reason(string& s, nested_exception const* nested)
{
    auto unity_exception = dynamic_cast<unity::Exception const*>(nested);
    auto std_exception = dynamic_cast<std::exception const*>(nested);

    if (unity_exception)
    {
        s += unity_exception->name();
        string reason = unity_exception->reason();
        if (!reason.empty())
        {
            s += ": " + reason;
        }
    }
    else if (std_exception)
    {
        s += std_exception->what();
    }

    // Append info about unknown std::exception and std::nested_exception.

    if (!unity_exception)
    {
        if (std_exception)
        {
            s += " (derived from std::exception and std::nested_exception)";
        }
        else
        {
            s += "std::nested_exception";
        }
    }
}

void follow_nested(string& s, nested_exception const* nested, int indent_level, std::string const& indent)
{
    if (nested->nested_ptr())
    {
        string margin = get_margin(indent_level, indent);

        s += ":\n";
        try
        {
            nested->rethrow_nested();
        }
        catch (std::nested_exception const& e)
        {
            auto unity_exception = dynamic_cast<unity::Exception const*>(&e);
            if (unity_exception)
            {
                s += unity_exception->to_string(indent_level + 1, indent);
            }
            else
            {
                s += margin + indent;
                print_name_and_reason(s, &e);
                follow_nested(s, &e, indent_level + 1, indent);
            }
        }
        catch (std::exception const& e)
        {
            s += margin + indent;
            s += e.what();                                    // Can show only what() for std::exception.
        }
        catch (...)
        {
            s += margin + indent;
            s += "unknown exception";                         // Best we can do for an exception whose type we don't know.
        }
    }
}

//
// Follow the history chain and print each exception in the chain.
//

void follow_history(string& s, int& count, unity::Exception const* e, int indent_level, std::string const& indent)
{
    if (!e->get_earlier())
    {
        count = 1;  // We have reached the oldest exception; set exception generation count and terminate recursion.
    }
    else
    {
        try
        {
            rethrow_exception(e->get_earlier());
        }
        catch (unity::Exception const& e)
        {
            // Recurse along the chain until we hit the end, then, as we pop back up the levels, we increment the
            // count and print it as a generation number for the exception information.
            // A bit like the "kicks" in "Inception", except that the deepest level is level 1...

            follow_history(s, count, &e, indent_level, indent);
        }
        ++count;
    }

    // Show info for this exception.

    s += "\n" + get_margin(indent_level, indent) + "Exception #";
    s += to_string(count) + ":\n";
    s += get_margin(indent_level, indent) + indent;
    print_name_and_reason(s, e);
    follow_nested(s, e, indent_level + 1, indent);
}

} // namespace

namespace unity
{

/**
\brief Constructs an exception instance.
\param name The fully-qualified name of the exception, such as `"unity::SyscallException"`. The name must not be empty.
\param reason Any additional details about the exception, such as an error message and the values of any members of the exception.
*/

Exception::Exception(string const& name, string const& reason)
    : name_(name)
    , reason_(reason)
{
    assert(!name_.empty());
}

//! @cond

Exception::Exception(Exception const&) = default;

Exception& Exception::operator=(Exception const&) = default;

Exception::~Exception() noexcept = default;

//! @endcond

/**
\brief Returns a string describing the exception, including any exceptions that were nested or chained.

\return The return value is the same string that is returned by calling to_string().
The returned pointer remains valid until the next call to what(), or until the exception is destroyed.
*/

char const* Exception::what() const noexcept
{
    try
    {
        what_ = to_string();
        return what_.c_str();
    }
    // LCOV_EXCL_START
    catch (std::exception const& e) // to_string() may throw (bad_alloc, in particular)
    {
        return e.what();
    }
    catch (...)
    {
        return "unknown exception";
    }
    // LCOV_EXCL_STOP
}

/**
\brief Returns the name set by the derived class's constructor.
*/

string Exception::name() const
{
    return name_;
}

/**
\brief Returns the reason set by the derived class's constructor (empty string if none).

Derived classes should include any other state information, such as the value of data members or
other relevant detail in the <code>reason</code> string they pass to the protected constructor.
*/

string Exception::reason() const
{
    return reason_;
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
    return to_string(0, indent);
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
    string margin = get_margin(indent_level, indent);
    string s = margin;
    s += name_;
    if (!reason_.empty())
    {
        s += ": " + reason_;
    }

    // Check whether there is an exception history and print each exception in the history.

    if (get_earlier())
    {
        s += "\n" + margin + indent + "Exception history:";
        try
        {
            rethrow_exception(get_earlier());
        }
        catch (unity::Exception const& e)
        {
            int count;
            follow_history(s, count, &e, indent_level + 2, indent);
        }
    }

    // Print this and any nested exceptions.

    follow_nested(s, this, indent_level, indent);

    return s;
}

/**
\brief Adds an exception to the exception history chain.

\param earlier_exception The parameter must be a <code>nullptr</code> or a <code>std::exception_ptr</code>
to an exception that was remembered earlier. This allows a sequence of exceptions to be remembered without
having to throw them and is useful, for example, in shutdown scenarios where any one of a sequence of steps
can fail, but we want to continue and try all the following steps and only throw after all of them have been
tried. In this case, each step that fails can add itself to the sequence of remembered exceptions, and finally
throw something like <code>ShutdownException</code>.
\return A <code>std::exception_ptr</code> to <code>this</code>.
*/

exception_ptr Exception::remember(exception_ptr earlier_exception)
{
    // Doesn't prevent loops, but protects against accidental self-assignment.

    if (earlier_ != earlier_exception)
    {
        earlier_ = earlier_exception;
    }
    return self();
}

/**
\brief Returns the previous exception.
\return Returns the next-older remembered exception, or <code>nullptr</code>, if none.
*/

exception_ptr Exception::get_earlier() const noexcept
{
    return earlier_;
}

} // namespace unity
