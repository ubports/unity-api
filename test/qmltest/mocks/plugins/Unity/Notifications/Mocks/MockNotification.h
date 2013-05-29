/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
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


#ifndef MOCKNOTIFICATION_H
#define MOCKNOTIFICATION_H

#include <unity/DllExport.h>

#include <unity/shell/notifications/NotificationInterface.h>

#include <QtCore/QVariantMap>

using namespace unity::shell::notifications;

class MockSource;
class MockModel;
class MockActionModel;

class UNITY_API MockNotification : public NotificationInterface
{
    friend class MockSource;
    friend class MockModel;
    friend class MockActionModel;

    Q_OBJECT
public:
    explicit MockNotification(QObject *parent = 0);

Q_SIGNALS:
    void completed();

private:
    QVariantMap m_data;
    MockActionModel* m_actions;
};

Q_DECLARE_METATYPE(MockNotification*)

#endif // MOCKNOTIFICATION_H
