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

#ifndef UNITY_EXCEPTIONS_H
#define UNITY_EXCEPTIONS_H

#include <unity/Exception.h>

namespace unity
{

/**
\brief Exception to indicate that an invalid argument was passed to a function, such as passing <code>nullptr</code>
       when the function expects the argument to be non-null.
*/

class UNITY_API InvalidArgumentException : public Exception
{
public:
    /**
    \brief Constructs the exception.
    \param reason Further details about the cause of the exception.
    */
    explicit InvalidArgumentException(std::string const& reason);
    //! @cond
    InvalidArgumentException(InvalidArgumentException const&);
    InvalidArgumentException& operator=(InvalidArgumentException const&);
    virtual ~InvalidArgumentException() noexcept;
    //! @endcond

    /**
    \brief Returns the fully-qualified name of the exception.
    */
    virtual char const* what() const noexcept override;

    /**
    \brief Returns a <code>std::exception_ptr</code> to <code>this</code>.
    */
    virtual std::exception_ptr self() const override;
};

/**
\brief Exception to indicate a logic error, such as driving the API incorrectly, such as calling methods
       in the wrong worder.
*/

class UNITY_API LogicException : public Exception
{
public:
    /**
    \brief Constructs the exception.
    \param reason Further details about the cause of the exception.
    */
    explicit LogicException(std::string const& reason);
    //! @cond
    LogicException(LogicException const&);
    LogicException& operator=(LogicException const&);
    virtual ~LogicException() noexcept;
    //! @endcond

    /**
    \brief Returns the fully-qualified name of the exception.
    */
    virtual char const* what() const noexcept override;

    /**
    \brief Returns a <code>std::exception_ptr</code> to <code>this</code>.
    */
    virtual std::exception_ptr self() const override;
};

/**
\brief Exception to indicate errors during shutdown.

       Usually, it is not possible to handle or recover
       from errors that arise during shutdown. This exception is thrown once all possible shutdown actions
       have been carried out and provides information about anything that went wrong via the exception
       chaining mechanism of the unity::Exception base class.
*/

class UNITY_API ShutdownException : public Exception
{
public:
    /**
    \brief Constructs the exception.
    \param reason Further details about the cause of the exception.
    */
    explicit ShutdownException(std::string const& reason);
    //! @cond
    ShutdownException(ShutdownException const&);
    ShutdownException& operator=(ShutdownException const&);
    virtual ~ShutdownException() noexcept;
    //! @endcond

    /**
    \brief Returns the fully-qualified name of the exception.
    */
    virtual char const* what() const noexcept override;

    /**
    \brief Returns a <code>std::exception_ptr</code> to <code>this</code>.
    */
    virtual std::exception_ptr self() const override;
};

namespace internal
{
class FileExceptionImpl;
}

/**
\brief Exception to indicate file I/O errors, such as failure to open or write to a file.
*/

class UNITY_API FileException : public Exception
{
public:
    /**
    \brief Constructs the exception.
    */
    /**
    \brief Constructs the exception from a reason string and and error number.
    \param reason Further details about the cause of the exception.
    \param err The UNIX <code>errno</code> value for the error.
    */
    FileException(std::string const& reason, int err);
    //! @cond
    FileException(FileException const&);
    FileException& operator=(FileException const&);
    virtual ~FileException() noexcept;
    //! @endcond

    /**
    \brief Returns the fully-qualified name of the exception.
    */
    virtual char const* what() const noexcept override;

    /**
    \brief Returns a <code>std::exception_ptr</code> to <code>this</code>.
    */
    virtual std::exception_ptr self() const override;

    /**
    \return Returns the error number that was passed to the constructor.
    */
    int error() const noexcept;

private:
    std::shared_ptr<internal::FileExceptionImpl> p_;
};

namespace internal
{
class SyscallExceptionImpl;
}

/**
\brief Exception to indicate system or library call errors that set <code>errno</code>.
*/

class UNITY_API SyscallException : public Exception
{
public:
    /**
    \brief Constructs the exception.
    */
    /**
    \brief Constructs the exception from a reason string and and error number.
    \param reason Further details about the cause of the exception.
    \param err The UNIX <code>errno</code> value for the error.
    */
    SyscallException(std::string const& reason, int err);
    //! @cond
    SyscallException(SyscallException const&);
    SyscallException& operator=(SyscallException const&);
    virtual ~SyscallException() noexcept;
    //! @endcond

    /**
    \brief Returns the fully-qualified name of the exception.
    */
    virtual char const* what() const noexcept override;

    /**
    \brief Returns a <code>std::exception_ptr</code> to <code>this</code>.
    */
    virtual std::exception_ptr self() const override;

    /**
    \return Returns the error number that was passed to the constructor.
    */
    int error() const noexcept;

private:
    //std::shared_ptr<internal::SyscallExceptionImpl> p_;
};

/**
\brief Exception for miscellaneous errors, such as failure of a third-party library or hitting resource limitations.
*/

class UNITY_API ResourceException : public Exception
{
public:
    /**
    \brief Constructs the exception.
    \param reason Further details about the cause of the exception.
    */
    explicit ResourceException(std::string const& reason);
    //! @cond
    ResourceException(ResourceException const&);
    ResourceException& operator=(ResourceException const&);
    virtual ~ResourceException() noexcept;
    //! @endcond

    /**
    \brief Returns the fully-qualified name of the exception.
    */
    virtual char const* what() const noexcept override;

    /**
    \brief Returns a <code>std::exception_ptr</code> to <code>this</code>.
    */
    virtual std::exception_ptr self() const override;
};

} // namespace unity

#endif
