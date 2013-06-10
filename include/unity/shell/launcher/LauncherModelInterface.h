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

#ifndef UNITY_LAUNCHER_LAUNCHERMODELINTERFACE_H
#define UNITY_LAUNCHER_LAUNCHERMODELINTERFACE_H

#include <unity/config.h>

#include <QtCore/QAbstractListModel>

namespace unity
{
namespace shell
{
namespace launcher
{

class LauncherItemInterface;

/**
 * @brief A list of launcher items to be displayed
 *
 * This model exposes all the launcher items that should be shown in the launcher.
 */

class UNITY_API LauncherModelInterface: public QAbstractListModel
{
   Q_OBJECT

protected:
    LauncherModelInterface(QObject *parent = 0): QAbstractListModel(parent) {}

public:
    enum Roles {
        RoleDesktopFile = Qt::UserRole,
        RoleName,
        RoleIcon,
        RoleFavorite,
        RoleRunning,
        RoleRecent,
        RoleProgress,
        RoleCount
    };

    virtual ~LauncherModelInterface() {}

    /**
     * @brief Move an item in the model.
     */
    Q_INVOKABLE virtual void move(int oldIndex, int newIndex) = 0;

    /**
     * @brief Get a launcher item.
     *
     * Note: QML requires the full namespace in the return value.
     *
     * @param index the index of the item to get
     * @returns The item.
     */
    Q_INVOKABLE virtual unity::shell::launcher::LauncherItemInterface *get(int index) const = 0;

    /// @cond
    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles.insert(RoleDesktopFile, "desktopFile");
        roles.insert(RoleName, "name");
        roles.insert(RoleIcon, "icon");
        roles.insert(RoleFavorite, "favorite");
        roles.insert(RoleRunning, "running");
        roles.insert(RoleRecent, "recent");
        roles.insert(RoleProgress, "progress");
        roles.insert(RoleCount, "count");
        return roles;
    }
    /// @endcond

};

}
}
}

#endif
