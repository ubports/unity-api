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

#include <Mocks/MockApplicationManager.h>
#include <Mocks/MockApplicationInfo.h>

using namespace unity::shell::application;

MockApplicationManager::MockApplicationManager(QObject* parent): ApplicationManagerInterface(parent)
{
    MockApplicationInfo *item = new MockApplicationInfo("phone-app", "Phone App", "This is a comment", QUrl("/usr/share/pixmaps/some/icon.png"));
    m_list.append(item);
/*    MockLauncherItem *item = new MockLauncherItem("phone-app", "/usr/share/applications/phone-app.desktop", "Phone", "phone-app");
    m_list.append(item);
    item = new MockLauncherItem("camera-app", "/usr/share/applications/camera-app.desktop", "Camera", "camera");
    m_list.append(item);
    item = new MockLauncherItem("gallery-app", "/usr/share/applications/gallery-app.desktop", "Gallery", "gallery");
    m_list.append(item);
    item = new MockLauncherItem("facebook-webapp", "/usr/share/applications/facebook-webapp.desktop", "Facebook", "facebook");
    m_list.append(item);
    item = new MockLauncherItem("webbrowser-app", "/usr/share/applications/webbrowser-app.desktop", "Browser", "browser");
    m_list.append(item);
    item = new MockLauncherItem("twitter-webapp", "/usr/share/applications/twitter-webapp.desktop", "Twitter", "twitter");
    m_list.append(item);
    item = new MockLauncherItem("gmail-webapp", "/usr/share/applications/gmail-webapp.desktop", "GMail", "gmail");
    m_list.append(item);
    item = new MockLauncherItem("ubuntu-weather-app", "/usr/share/applications/ubuntu-weather-app.desktop", "Weather", "weather");
    m_list.append(item);
    item = new MockLauncherItem("notes-app", "/usr/share/applications/notes-app.desktop", "Notepad", "notepad");
    m_list.append(item);
    item = new MockLauncherItem("ubuntu-calendar-app", "/usr/share/applications/ubuntu-calendar-app.desktop","Calendar", "calendar");
    m_list.append(item);
*/
}

MockApplicationManager::~MockApplicationManager()
{
    while (!m_list.empty())
    {
        m_list.takeFirst()->deleteLater();
    }
}

// cppcheck-suppress unusedFunction
int MockApplicationManager::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_list.count();
}

QVariant MockApplicationManager::data(const QModelIndex& index, int role) const
{
    ApplicationInfoInterface *item = m_list.at(index.row());
    switch(role)
    {
    case RoleAppId:
        return item->appId();
    case RoleName:
        return item->name();
    case RoleComment:
        return item->comment();
    case RoleIcon:
        return item->icon();
    case RoleStage:
        return item->stage();
    case RoleState:
        return item->state();
    case RoleFocused:
        return item->focused();
    }

    return QVariant();
}

unity::shell::application::ApplicationInfoInterface *MockApplicationManager::get(int index) const
{
    if (index < 0 || index >= m_list.count())
    {
        return 0;
    }
    return m_list.at(index);
}

unity::shell::application::ApplicationInfoInterface *MockApplicationManager::focusedApplication() const
{
    return m_list.first();
}

void MockApplicationManager::focusApplication(ApplicationInfoInterface *application)
{
    Q_UNUSED(application)
}

void MockApplicationManager::unfocusCurrentApplication()
{
}

unity::shell::application::ApplicationInfoInterface *MockApplicationManager::startProcess(const QString &appId, const QStringList &arguments)
{
    Q_UNUSED(appId)
    Q_UNUSED(arguments)
    return 0;
}

void MockApplicationManager::stopProcess(unity::shell::application::ApplicationInfoInterface *application)
{
    Q_UNUSED(application)
}
