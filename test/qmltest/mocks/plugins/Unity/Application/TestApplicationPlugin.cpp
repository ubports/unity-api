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
 *      Michael Zanetti <michael.zanetti@canonical.com>
 */

#include <TestApplicationPlugin.h>
#include <Mocks/MockApplicationManager.h>
#include <Mocks/MockApplicationInfo.h>

#include <ApplicationManagerInterface.h>
#include <ApplicationInfoInterface.h>

#include <QtQml/qqml.h>

using namespace unity::shell::application;

static QObject* modelProvider(QQmlEngine* /* engine */, QJSEngine* /* scriptEngine */)
{
    return new MockApplicationManager();
}

// cppcheck-suppress unusedFunction
void TestApplicationPlugin::registerTypes(const char* uri)
{
    // @uri Unity.Application
    qmlRegisterUncreatableType<ApplicationManagerInterface>(uri, 0, 1, "ApplicationManagerInterface", "Interface for the ApplicationManager");
    qmlRegisterUncreatableType<ApplicationInfoInterface>(uri, 0, 1, "ApplicationInfoInterface", "Interface for the ApplicationInfo");

    qmlRegisterSingletonType<MockApplicationManager>(uri, 0, 1, "ApplicationManager", modelProvider);
    qmlRegisterUncreatableType<MockApplicationInfo>(uri, 0, 1, "ApplicationInfo", "Can't create ApplicationInfos in QML. Get them from the ApplicationManager");
}
