/*
 * Copyright (C) 2012 Canonical Ltd
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

#include <unity/ExceptionImplBase.h>
#include <unity/Exception.h>

using namespace std;

namespace unity
{

namespace internal
{

class ExceptionData
{
public:
    ExceptionData(Exception const* owner, string const& reason)
        : owner_(owner)
        , reason_(reason)
        , earlier_(nullptr)
    {
    }

    ExceptionData(ExceptionData const&) = delete;
    ExceptionData& operator=(ExceptionData const&) = delete;

    Exception const* owner_;
    string reason_;
    std::exception_ptr earlier_;
};

}

/**
\brief Instantiates an implementation instance for a unity::Exception.
\param owner This must be set to the `this` pointer of the exception that owns this implementation.
\param reason Further details about the cause of the exception.
*/

ExceptionImplBase::ExceptionImplBase(Exception const* owner, string const& reason)
    : p_(make_shared<internal::ExceptionData>(owner, reason))
{
}

//! @cond

ExceptionImplBase::~ExceptionImplBase() noexcept = default;

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
    // Add the what() string if this is a std::exception.

    std::exception const* std_exception = dynamic_cast<std::exception const*>(nested);
    if (std_exception)
    {
        s += std_exception->what();
    }

    // Add the reason if this is a unity::Exception.

    unity::Exception const* unity_exception = dynamic_cast<unity::Exception const*>(nested);
    if (unity_exception)
    {
        string reason = unity_exception->reason();
        if (!reason.empty())
        {
            s += ": " + reason;
        }
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
            unity::Exception const* ge = dynamic_cast<unity::Exception const*>(&e);
            if (ge)
            {
                s += ge->to_string(indent_level + 1, indent);
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

//! @endcond

/**
\brief Returns the reason set by the derived class's constructor (empty string if none).

Derived classes should include any other state information, such as the value of data members or
other relevant detail in the <code>reason</code> string they pass to the protected constructor.
*/

string ExceptionImplBase::reason() const
{
    return p_->reason_;
}

/**
\brief Returns a string describing the exception, including any exceptions that were nested or chained.

Nested exceptions are indented according to their nesting level. If the exception contains chained
exceptions, these are shown in oldest-to-newest order.

\param nested This must be set to the `this` pointer of the exception that owns this implementation.

\param indent_level This controls the indent level. The value <code>0</code> indicates
       the outermost level (no indent).
\param indent This controls the amount of indenting per level. The default indent is four spaces.
\return The string describing the exception.
*/

string ExceptionImplBase::to_string(nested_exception const* nested, int indent_level, string const& indent) const
{
    string margin = get_margin(indent_level, indent);
    string s = margin;
    s += dynamic_cast<const std::exception*>(nested)->what();

    string r = reason();
    if (!r.empty())
    {
        s += ": " + r;
    }

    // Check whether there is an exception history and print each exception in the history.

    unity::Exception const* unity_exception(dynamic_cast<unity::Exception const*>(nested));
    if (unity_exception && unity_exception->get_earlier())
    {
        s += "\n" + margin + indent + "Exception history:";
        try
        {
            rethrow_exception(unity_exception->get_earlier());
        }
        catch (unity::Exception const& e)
        {
            int count;
            follow_history(s, count, &e, indent_level + 2, indent);
        }
    }

    // Print this and any nested exceptions.

    follow_nested(s, nested, indent_level, indent);

    return s;
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

exception_ptr ExceptionImplBase::set_earlier(exception_ptr earlier_exception)
{
    // Doesn't prevent loops, but protects against accidental self-assignment.

    if (p_->earlier_ != earlier_exception)
    {
        p_->earlier_ = earlier_exception;
    }
    return p_->owner_->self();
}

/**
\brief Returns the previous exception.
\return Returns the next-older remembered exception, or <code>nullptr</code>, if none.
*/

exception_ptr ExceptionImplBase::get_earlier() const noexcept
{
    return p_->earlier_;
}

} // namespace unity
