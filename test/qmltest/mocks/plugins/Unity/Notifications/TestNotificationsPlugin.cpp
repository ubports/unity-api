/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
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


#include <TestNotificationsPlugin.h>
#include <Mocks/MockModel.h>
#include <Mocks/MockSource.h>
#include <Mocks/MockNotification.h>

#include <unity/shell/notifications/Enums.h>
#include <unity/shell/notifications/ModelInterface.h>
#include <unity/shell/notifications/SourceInterface.h>
#include <unity/shell/notifications/NotificationInterface.h>

#include <qqml.h>

using namespace unity::shell::notifications;

static QObject* modelProvider(QQmlEngine* /* engine */, QJSEngine* /* scriptEngine */)
{
    return new MockModel();
}

static QObject* sourceProvider(QQmlEngine* /* engine */, QJSEngine* /* scriptEngine */)
{
    return new MockSource();
}

void TestNotificationsPlugin::registerTypes(const char *uri)
{
    // @uri Unity.Notifications
    qmlRegisterUncreatableType<Urgency>(uri, 0, 1, "Urgency", "Urgency is just a enum wrapper");
    qmlRegisterUncreatableType<Type>(uri, 0, 1, "Type", "Type is just a enum wrapper");
    qmlRegisterUncreatableType<Hint>(uri, 0, 1, "Hint", "Hint is just a enum wrapper");
    qmlRegisterUncreatableType<NotificationInterface>(uri, 0, 1, "NotificationInterface", "NotificationInterface is an abstract base class");
    qmlRegisterUncreatableType<ModelInterface>(uri, 0, 1, "ModelInterface", "ModelInterface is an abstract base class");
    qmlRegisterUncreatableType<SourceInterface>(uri, 0, 1, "SourceInterface", "SourceInterface is an abstract base class");

    qmlRegisterUncreatableType<MockNotification>(uri, 0, 1, "Notification", "Notification objects can only be created by the plugin");
    qmlRegisterSingletonType<MockSource>(uri, 0, 1, "Source", sourceProvider);
    qmlRegisterSingletonType<MockModel>(uri, 0, 1, "Model", modelProvider);
}
