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


class UNITY_API NotificationInterface : public QObject
{
    Q_OBJECT
public:
    explicit NotificationInterface(QObject* parent = 0) : QObject(parent) { }
    virtual ~NotificationInterface() { }

public Q_SLOTS:
    virtual void onHovered() = 0;
    virtual void onDisplayed() = 0;
    virtual void invokeAction(const QString& id) = 0;

Q_SIGNALS:
    void dismissed();
};

} // namespace notifications

} // namespace shell

} // namespace unity

#endif // UNITY_SHELL_NOTIFICATIONS_NOTIFICATIONINTERFACE_H
