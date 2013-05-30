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

#include <unity/SymbolExport.h>

#include <QtCore/QObject>

namespace unity
{

namespace shell
{

namespace notifications
{

/**
\brief A Notification object

This class exposes signals used by the UI to communicate the state
of a notification.
*/

class UNITY_API NotificationInterface : public QObject
{
    Q_OBJECT

protected:
    /// @cond
    explicit NotificationInterface(QObject* parent = 0) : QObject(parent) { }
    /// @endcond

public:
    virtual ~NotificationInterface() { }

Q_SIGNALS:
    /**
    Will be called whenever the mouse hover status of a notification changes.

    \param hovered Mouse hover status of this notification.
    */
    void hovered(bool hovered);

    /**
    Will be called whenever the display status of a notification changes.

    \param displayed Visible/hidden status of this notification.
    */
    void displayed(bool displayed);

    /**
    Will be called whenever the notification was dismissed. This can be called internally
    by the notification implementation (e.g. timeout) or from the UI when the user dismisses
    a notification.
    */
    void dismissed();

    /**
    Will be called whenever an action of this notification is to be invoked.

    \param id Id of the invoked action.
    */
    void actionInvoked(const QString& id);
};

} // namespace notifications

} // namespace shell

} // namespace unity

#endif // UNITY_SHELL_NOTIFICATIONS_NOTIFICATIONINTERFACE_H
