/*
 * Copyright (C) 2013 Canonical Ltd
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

#include <gtest/gtest.h>

using namespace std;
using namespace unity;

//
// Check Exception base class functionality (copy, assignment, accessor methods, etc.)
//

TEST(Exception, basic)
{
    SyscallException e("Hello", 0);
    EXPECT_EQ("unity::SyscallException", e.name());
    EXPECT_EQ("Hello (errno = 0)", e.reason());
    EXPECT_STREQ("unity::SyscallException: Hello (errno = 0)", e.what());

    SyscallException e2(e);
    EXPECT_EQ(e.name(), e2.name());
    EXPECT_EQ(e.reason(), e2.reason());
    EXPECT_STREQ(e.what(), e2.what());

    SyscallException e3("blah", 1);
    e2 = e3;
    EXPECT_EQ(e3.name(), e2.name());
    EXPECT_EQ(e3.reason(), e2.reason());
    EXPECT_STREQ(e3.what(), e2.what());

    EXPECT_EQ("unity::SyscallException: blah (errno = 1)", e3.to_string());
    EXPECT_EQ("unity::SyscallException: blah (errno = 1)", e3.to_string(0, "    "));
    EXPECT_EQ("        unity::SyscallException: blah (errno = 1)", e3.to_string(1, "        "));
    EXPECT_EQ("                unity::SyscallException: blah (errno = 1)", e3.to_string(2, "        "));

    try
    {
        throw e;
    }
    catch (Exception& e)
    {
        EXPECT_STREQ("unity::SyscallException: Hello (errno = 0)", e.what());
    }
}

TEST(Exception, empty_reason)
{
    {
        InvalidArgumentException e("");
        EXPECT_EQ("", e.reason());
        EXPECT_STREQ("unity::InvalidArgumentException", e.what());
    }

    {
        SyscallException e("", 0);
        EXPECT_EQ("(errno = 0)", e.reason());
        EXPECT_STREQ("unity::SyscallException: (errno = 0)", e.what());
    }
}

//
// A few helper functions so we can test that the nesting works correctly.
//

void a()
{
    throw bad_alloc();
}

void b()
{
    try
    {
        a();
    }
    catch (...)
    {
        throw InvalidArgumentException("a() threw");
    }
}

void c()
{
    try
    {
        b();
    }
    catch (nested_exception const&)
    {
        throw InvalidArgumentException("b() threw");
    }
}

class E : public std::exception, public nested_exception
{
public:
    virtual char const* what() const noexcept
    {
        return "E";
    }
    E() = default;
    ~E() noexcept {}
};

void throw_E()
{
    try
    {
        c();
    }
    catch (...)
    {
        throw E();
    }
}

void d()
{
    try
    {
        throw_E();
    }
    catch (...)
    {
        throw InvalidArgumentException("throw_E() threw");
    }
}

struct N : public nested_exception
{
};

void throw_N()
{
    try
    {
        b();
    }
    catch (...)
    {
        throw N();
    }
}

void f()
{
    try
    {
        throw_N();
    }
    catch (...)
    {
        throw InvalidArgumentException("throw_N() threw");
    }
}

void throw_unknown()
{
    throw 42;
}

void g()
{
    try
    {
        throw_unknown();
    }
    catch (...)
    {
        throw InvalidArgumentException("throw_unknown threw");
    }
}

TEST(Exception, nesting)
{
    // Check basic chaining works and terminates correctly on a std::exception.

    try
    {
        c();
    }
    catch (Exception const& e)
    {
        EXPECT_EQ("unity::InvalidArgumentException: b() threw:\n"
                  "    unity::InvalidArgumentException: a() threw:\n"
                  "        std::bad_alloc", e.to_string());
    }

    // Check that we follow the chain for exceptions we don't know, but that derive
    // from both std::exception and std::nested_exception.

    try
    {
        d();
    }
    catch (Exception const& e)
    {
        EXPECT_EQ("unity::InvalidArgumentException: throw_E() threw:\n"
                  "    E (derived from std::exception and std::nested_exception):\n"
                  "        unity::InvalidArgumentException: b() threw:\n"
                  "            unity::InvalidArgumentException: a() threw:\n"
                  "                std::bad_alloc", e.to_string());
    }

    // Check that we follow the chain for exceptions that are derived from std::nested_exception
    // but not std::exception.

    try
    {
        f();
    }
    catch (unity::Exception const& e)
    {
        EXPECT_EQ("unity::InvalidArgumentException: throw_N() threw:\n"
                  "    std::nested_exception:\n"
                  "        unity::InvalidArgumentException: a() threw:\n"
                  "            std::bad_alloc", e.to_string());
    }

    // Check that we are correctly dealing with unknown exceptions

    try
    {
        g();
    }
    catch (unity::Exception const& e)
    {
        EXPECT_EQ("unity::InvalidArgumentException: throw_unknown threw:\n"
                  "    unknown exception", e.to_string());
    }
}

//
// Test the history chaining.
//

TEST(Exception, history)
{
    // Check that remember() and get_earlier() return the correct exception.

    {
        InvalidArgumentException e("");
        EXPECT_EQ(nullptr, e.get_earlier());
        exception_ptr ep = make_exception_ptr(e);

        InvalidArgumentException e2("");
        e2.remember(ep);
        EXPECT_EQ(e2.get_earlier(), ep);
    }

    // Check that we are following the history chain.

    {
        exception_ptr ep;
        try
        {
            throw InvalidArgumentException("Step 1");
        }
        catch (Exception& e)
        {
            ep = e.remember(ep);
        }
        InvalidArgumentException e2("Step 2");
        ep = e2.remember(ep);

        try
        {
            ShutdownException e("Finalization problem");
            e.remember(ep);
            throw e;
        }
        catch (Exception const& e)
        {
            string reason = e.to_string();
            EXPECT_EQ("unity::ShutdownException: Finalization problem\n"
                      "    Exception history:\n"
                      "        Exception #1:\n"
                      "            unity::InvalidArgumentException: Step 1\n"
                      "        Exception #2:\n"
                      "            unity::InvalidArgumentException: Step 2", e.to_string());
        }
    }

    // Same test, but this time with nested exceptions in the history.

    {
        exception_ptr ep;
        try
        {
            c();
        }
        catch (Exception& e)
        {
            ep = e.remember(ep);
        }
        try
        {
            f();
        }
        catch (Exception &e)
        {
            ep = e.remember(ep);
        }

        try
        {
            ShutdownException e("Finalization problem");
            e.remember(ep);
            throw e;
        }
        catch (Exception const& e)
        {
            string reason = e.to_string();
            EXPECT_EQ("unity::ShutdownException: Finalization problem\n"
                      "    Exception history:\n"
                      "        Exception #1:\n"
                      "            unity::InvalidArgumentException: b() threw:\n"
                      "                unity::InvalidArgumentException: a() threw:\n"
                      "                    std::bad_alloc\n"
                      "        Exception #2:\n"
                      "            unity::InvalidArgumentException: throw_N() threw:\n"
                      "                std::nested_exception:\n"
                      "                    unity::InvalidArgumentException: a() threw:\n"
                      "                        std::bad_alloc", e.to_string());
        }
    }

    // Same test, but this time with history in a nested exception.

    {
        exception_ptr ep;
        try
        {
            c();
        }
        catch (Exception& e)
        {
            ep = e.remember(ep);
        }
        try
        {
            f();
        }
        catch (Exception &e)
        {
            ep = e.remember(ep);
        }

        try
        {
            try
            {
                ShutdownException e("Finalization problem");
                e.remember(ep);
                throw e;
            }
            catch (Exception &e)
            {
                throw ShutdownException("Cannot finalize");
            }
        }
        catch (Exception const& e)
        {
            EXPECT_EQ("unity::ShutdownException: Cannot finalize:\n"
                      "    unity::ShutdownException: Finalization problem\n"
                      "        Exception history:\n"
                      "            Exception #1:\n"
                      "                unity::InvalidArgumentException: b() threw:\n"
                      "                    unity::InvalidArgumentException: a() threw:\n"
                      "                        std::bad_alloc\n"
                      "            Exception #2:\n"
                      "                unity::InvalidArgumentException: throw_N() threw:\n"
                      "                    std::nested_exception:\n"
                      "                        unity::InvalidArgumentException: a() threw:\n"
                      "                            std::bad_alloc", e.to_string());
        }
    }
}

//
// Tests for the state of concrete derived exceptions follow.
//

TEST(SyscallException, state)
{
    // Check that we correctly mention the error code.

    {
        SyscallException e("without error", 0);
        EXPECT_EQ("unity::SyscallException: without error (errno = 0)", e.to_string());
        SyscallException e2("blah", 0);
        e2 = e;
        EXPECT_EQ(e.reason(), e2.reason());
    }

    {
        SyscallException e("with error code", 42);
        EXPECT_EQ("unity::SyscallException: with error code (errno = 42)", e.to_string());
        EXPECT_EQ(e.error(), 42);
        EXPECT_THROW(rethrow_exception(e.self()), SyscallException);
    }

    {
        SyscallException e("with errno", EPERM);
        EXPECT_EQ("unity::SyscallException: with errno (errno = 1)", e.to_string());
        EXPECT_EQ(e.error(), EPERM);
        EXPECT_THROW(rethrow_exception(e.self()), SyscallException);
    }
}

TEST(InvalidArgumentException, state)
{
    {
        InvalidArgumentException e("bad arg");
        EXPECT_STREQ("unity::InvalidArgumentException: bad arg", e.what());
        EXPECT_THROW(rethrow_exception(e.self()), InvalidArgumentException);
        InvalidArgumentException e2("blah");
        e2 = e;
        EXPECT_EQ(e.reason(), e2.reason());
    }
}

TEST(LogicException, state)
{
    {
        LogicException e("You shouldn't have done that!");
        EXPECT_STREQ("unity::LogicException: You shouldn't have done that!", e.what());
        EXPECT_THROW(rethrow_exception(e.self()), LogicException);
        LogicException e2("blah");
        e2 = e;
        EXPECT_EQ(e.reason(), e2.reason());
    }
}

TEST(ShutdownException, state)
{
    {
        ShutdownException e("Need some kicks");
        EXPECT_STREQ("unity::ShutdownException: Need some kicks", e.what());
        EXPECT_THROW(rethrow_exception(e.self()), ShutdownException);
        ShutdownException e2("blah");
        e2 = e;
        EXPECT_EQ(e.reason(), e2.reason());
    }
}

TEST(FileException, state)
{
    {
        FileException e("File error", 0);
        EXPECT_EQ("File error (errno = 0)", e.reason());
        EXPECT_STREQ("unity::FileException: File error (errno = 0)", e.what());
        EXPECT_EQ(0, e.error());
        EXPECT_THROW(rethrow_exception(e.self()), FileException);
        FileException e2("blah", 0);
        e2 = e;
        EXPECT_EQ(e.reason(), e2.reason());
        EXPECT_EQ(e.error(), e2.error());
    }

    {
        FileException e("File error", 42);
        EXPECT_EQ("File error (errno = 42)", e.reason());
        EXPECT_STREQ("unity::FileException: File error (errno = 42)", e.what());
        EXPECT_EQ(42, e.error());
        EXPECT_THROW(rethrow_exception(e.self()), FileException);
        FileException e2("blah", 0);
        e2 = e;
        EXPECT_EQ(e.reason(), e2.reason());
        EXPECT_EQ(e.error(), e2.error());
    }
}

TEST(ResourceException, state)
{
    {
        ResourceException e("Need some kicks");
        EXPECT_STREQ("unity::ResourceException: Need some kicks", e.what());
        EXPECT_THROW(rethrow_exception(e.self()), ResourceException);
        ResourceException e2("blah");
        e2 = e;
        EXPECT_EQ(e.reason(), e2.reason());
    }
}

// Dynamic allocation to get around bogus function coverage reports by gcov.

TEST(Exceptions, dynamic)
{
    {
        SyscallException* ep = new SyscallException("Hello", 0);
        delete ep;
    }

    {
        InvalidArgumentException* ep = new InvalidArgumentException("Hello");
        delete ep;
    }

    {
        LogicException* ep = new LogicException("Hello");
        delete ep;
    }

    {
        ShutdownException* ep = new ShutdownException("Hello");
        delete ep;
    }

    {
        FileException* ep = new FileException("Hello", 0);
        delete ep;
    }

    {
        ResourceException* ep = new ResourceException("Hello");
        delete ep;
    }
}
