/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Michał Sawicz <michal.sawicz@canonical.com>
 */


#ifndef UNITY_SHELL_NOTIFICATIONS_MODELINTERFACE_H
#define UNITY_SHELL_NOTIFICATIONS_MODELINTERFACE_H

#include <unity/config.h>

#include <QtCore/QAbstractListModel>

namespace unity
{

namespace shell
{

namespace notifications
{


/**
\brief A list of notifications to be displayed

This model exposes all the notifications that are currently supposed to be on screen.
Not all of them might actually get on screen due to screen size, in which case the
Notification::displayed(true) signal will only be emitted after the Notification was
actually displayed.
*/

class UNITY_API ModelInterface : public QAbstractListModel
{
    Q_OBJECT

    /**
    \brief Whether a placeholder for confirmation should be kept at the beginning

    When this is true, the model should hold a Placeholder type notification at the top
    and update its data when an incoming Confirmation type notification is sent.

    \accessors %confirmationPlaceholder(), setConfirmationPlaceholder(bool confirmationPlaceholder)
    \notifier confirmationPlaceholderChanged(bool confirmationPlaceholder)
    */
    Q_PROPERTY(bool confirmationPlaceholder READ confirmationPlaceholder WRITE setConfirmationPlaceholder NOTIFY confirmationPlaceholderChanged)

public:
    /// @cond
    explicit ModelInterface(QObject* parent = 0) : QAbstractListModel(parent) { }
    virtual ~ModelInterface() { }
    /// @endcond

    /// @cond
    virtual bool confirmationPlaceholder() const = 0;
    virtual void setConfirmationPlaceholder(bool confirmationPlaceholder) = 0;
    /// @endcond

Q_SIGNALS:
    /**
    Emitted when value of the confirmationPlaceholder property has changed.

    \param confirmationPlaceholder New value of the confirmationPlaceholder property.
    */
    void confirmationPlaceholderChanged(bool confirmationPlaceholder);
};

} // namespace notifications

} // namespace shell

} // namespace unity

#endif // UNITY_SHELL_NOTIFICATIONS_MODELINTERFACE_H
