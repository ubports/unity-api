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


#ifndef UNITY_SHELL_NOTIFICATIONS_NOTIFICATIONINTERFACE_H
#define UNITY_SHELL_NOTIFICATIONS_NOTIFICATIONINTERFACE_H

#include <unity/config.h>

#include <QtCore/QObject>

namespace unity
{

namespace shell
{

namespace notifications
{

/**
\brief A Notification object

This class exposes slots and signals used for the UI to communicate the state
of a notification.
*/

class UNITY_API NotificationInterface : public QObject
{
    Q_OBJECT

public:
    /// @cond
    explicit NotificationInterface(QObject* parent = 0) : QObject(parent) { }
    virtual ~NotificationInterface() { }
    /// @endcond

public Q_SLOTS:
    /**
    Will be called whenever the mouse hover status of a notification changes.

    \param hovered Mouse hover status of this notification.
    */
    virtual void onHovered(bool hovered) = 0;
    /**
    Will be called whenever the display status of a notification changes.

    \param displayed Visible/hidden status of this notification.
    */
    virtual void onDisplayed(bool displayed) = 0;
    /**
    Will be called whenever an action of this notification is to be invoked.

    \param id Id of the invoked action.
    */
    virtual void invokeAction(const QString& id) = 0;

Q_SIGNALS:
    /**
    Should be emitted whenever the notification was dismissed. This can be called internally
    by the notification implementation (e.g. timeout) or from the UI when the user dismisses
    a notification.
    */
    void dismissed();
};

} // namespace notifications

} // namespace shell

} // namespace unity

#endif // UNITY_SHELL_NOTIFICATIONS_NOTIFICATIONINTERFACE_H
