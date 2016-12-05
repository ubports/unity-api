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

#include <TestLauncherPlugin.h>
#include <Mocks/MockLauncherModel.h>
#include <Mocks/MockLauncherItem.h>
#include <Mocks/MockQuickListModel.h>
#include <Mocks/MockAppDrawerModel.h>

#include <LauncherModelInterface.h>
#include <LauncherItemInterface.h>
#include <AppDrawerModelInterface.h>

#include <QtQml/qqml.h>

using namespace unity::shell::launcher;
using namespace unity::shell::application;

static QObject* modelProvider(QQmlEngine* /* engine */, QJSEngine* /* scriptEngine */)
{
    return new MockLauncherModel();
}

// cppcheck-suppress unusedFunction
void TestLauncherPlugin::registerTypes(const char* uri)
{
    // @uri Unity.Launcher
    qmlRegisterUncreatableType<LauncherModelInterface>(uri, 0, 1, "LauncherModelInterface", "Interface for the LauncherModel");
    qmlRegisterUncreatableType<LauncherItemInterface>(uri, 0, 1, "LauncherItemInterface", "Interface for the LauncherItem");
    qmlRegisterUncreatableType<QuickListModelInterface>(uri, 0, 1, "QuickListModelInterface", "Interface for the QuickListModel");
    qmlRegisterUncreatableType<AppDrawerModelInterface>(uri, 0, 1, "AppDrawerModelInterface", "Interface for the AppDrawerModel");

    qmlRegisterSingletonType<MockLauncherModel>(uri, 0, 1, "LauncherModel", modelProvider);
    qmlRegisterUncreatableType<MockLauncherItem>(uri, 0, 1, "LauncherItem", "Can't create LauncherItems in QML. Get them from the LauncherModel");
    qmlRegisterUncreatableType<MockQuickListModel>(uri, 0, 1, "QuickListModel", "Can't create QuickListModels in QML. Get them from the LauncherItems");
    qmlRegisterType<MockAppDrawerModel>(uri, 0, 1, "AppDrawerModel");

    // Need to register the appmanager here ourselves as there won't be a real AppManager plugin in this test
    qmlRegisterUncreatableType<unity::shell::application::ApplicationManagerInterface>(uri, 0, 1, "ApplicationManagerInterface", "Interface for the ApplicationManager");
}
