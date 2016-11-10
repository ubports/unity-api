/*
 * Copyright 2016 Canonical Ltd.
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
 */

#include <Mocks/MockAppDrawerModel.h>
#include <Mocks/MockLauncherItem.h>

using namespace unity::shell::launcher;

MockAppDrawerModel::MockAppDrawerModel(QObject* parent): AppDrawerModelInterface(parent)
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

MockAppDrawerModel::~MockAppDrawerModel()
{
    while (!m_list.empty())
    {
        m_list.takeFirst()->deleteLater();
    }
}

// cppcheck-suppress unusedFunction
int MockAppDrawerModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_list.count();
}

QVariant MockAppDrawerModel::data(const QModelIndex& index, int role) const
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
    case RoleUsage:
        return 1;
    }

    return QVariant();
}
