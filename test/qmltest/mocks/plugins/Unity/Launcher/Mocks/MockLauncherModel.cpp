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

#include <Mocks/MockLauncherModel.h>
#include <Mocks/MockLauncherItem.h>

#include "../../Application/Mocks/MockApplicationManager.h"

using namespace unity::shell::launcher;

MockLauncherModel::MockLauncherModel(QObject* parent): LauncherModelInterface(parent)
{
    MockLauncherItem *item = new MockLauncherItem("phone-app", "/usr/share/applications/phone-app.desktop", "Phone", "phone-app", this);
    m_list.append(item);
    item = new MockLauncherItem("camera-app", "/usr/share/applications/camera-app.desktop", "Camera", "camera", this);
    m_list.append(item);
    item = new MockLauncherItem("gallery-app", "/usr/share/applications/gallery-app.desktop", "Gallery", "gallery", this);
    m_list.append(item);
    item = new MockLauncherItem("facebook-webapp", "/usr/share/applications/facebook-webapp.desktop", "Facebook", "facebook", this);
    m_list.append(item);
    item = new MockLauncherItem("webbrowser-app", "/usr/share/applications/webbrowser-app.desktop", "Browser", "browser", this);
    m_list.append(item);
    item = new MockLauncherItem("twitter-webapp", "/usr/share/applications/twitter-webapp.desktop", "Twitter", "twitter", this);
    m_list.append(item);
    item = new MockLauncherItem("gmail-webapp", "/usr/share/applications/gmail-webapp.desktop", "GMail", "gmail", this);
    m_list.append(item);
    item = new MockLauncherItem("ubuntu-weather-app", "/usr/share/applications/ubuntu-weather-app.desktop", "Weather", "weather", this);
    m_list.append(item);
    item = new MockLauncherItem("notes-app", "/usr/share/applications/notes-app.desktop", "Notepad", "notepad", this);
    m_list.append(item);
    item = new MockLauncherItem("ubuntu-calendar-app", "/usr/share/applications/ubuntu-calendar-app.desktop","Calendar", "calendar", this);
    m_list.append(item);
}

MockLauncherModel::~MockLauncherModel()
{
    while (!m_list.empty())
    {
        m_list.takeFirst()->deleteLater();
    }
}

// cppcheck-suppress unusedFunction
int MockLauncherModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_list.count();
}

QVariant MockLauncherModel::data(const QModelIndex& index, int role) const
{
    LauncherItemInterface *item = m_list.at(index.row());
    switch(role)
    {
    case RoleAppId:
        return item->appId();
    case RoleName:
        return item->name();
    case RoleIcon:
        return item->icon();
    case RolePinned:
        return item->pinned();
    case RoleRunning:
        return item->running();
    case RoleRecent:
        return item->recent();
    case RoleProgress:
        return item->progress();
    case RoleCount:
        return item->count();
    case RoleCountVisible:
        return item->countVisible();
    case RoleFocused:
        return item->focused();
    case RoleAlerting:
        return item->alerting();
    }

    return QVariant();
}

LauncherItemInterface *MockLauncherModel::get(int index) const
{
    if (index < 0 || index >= m_list.count())
    {
        return 0;
    }
    return m_list.at(index);
}

void MockLauncherModel::setAlerting(const QString &appId, bool alerting) {
    Q_UNUSED(appId)
    Q_UNUSED(alerting)
}

void MockLauncherModel::move(int oldIndex, int newIndex)
{
    Q_UNUSED(oldIndex)
    Q_UNUSED(newIndex)
}

void MockLauncherModel::pin(const QString &appId, int index)
{
    Q_UNUSED(appId)
    Q_UNUSED(index)
}

void MockLauncherModel::requestRemove(const QString &appId)
{
    Q_UNUSED(appId)
}

void MockLauncherModel::quickListActionInvoked(const QString &appId, int actionIndex)
{
    Q_UNUSED(appId)
    Q_UNUSED(actionIndex)
}

void MockLauncherModel::setUser(const QString &user)
{
    Q_UNUSED(user)
}

unity::shell::application::ApplicationManagerInterface *MockLauncherModel::applicationManager() const
{
    unity::shell::application::ApplicationManagerInterface* appManager = new MockApplicationManager();
    appManager->deleteLater();
    return appManager;
}

void MockLauncherModel::setApplicationManager(unity::shell::application::ApplicationManagerInterface *applicationManager)
{
    Q_UNUSED(applicationManager)
}

bool MockLauncherModel::onlyPinned() const
{
    return false;
}

void MockLauncherModel::setOnlyPinned(bool onlyPinned)
{
    Q_UNUSED(onlyPinned)
}
