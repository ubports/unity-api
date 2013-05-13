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


#include <Mocks/mocknotificationsplugin.h>
#include <Mocks/mocksource.h>

#include <unity/shell/notifications/source.h>

#include <qqml.h>

using namespace unity::shell::notifications;

void MockNotificationsPlugin::registerTypes(const char *uri)
{
    // @uri Unity.Notifications.Mocks
    qmlRegisterUncreatableType<SourceInterface>(uri, 0, 1, "SourceInterface", "SourceInterface is an abstract base class");

    qmlRegisterType<MockSource>(uri, 0, 1, "MockSource");
}
