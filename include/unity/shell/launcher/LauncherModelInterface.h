/*
 * Copyright (C) 2011 Canonical, Ltd.
 *
 * Authors:
 *  Michael Zanetti <michael.zanetti@canonical.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LAUNCHERMODELINTERFACE_H
#define LAUNCHERMODELINTERFACE_H

#include <unity/config.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace launcher
{

class LauncherItemInterface;

class UNITY_API LauncherModelInterface: public QAbstractListModel
{
   Q_OBJECT

public:
    enum Roles {
        RoleDesktopFile = Qt::UserRole,
        RoleName,
        RoleIcon,
        RoleFavorite,
        RoleRunning,
        RoleRecent
    };

    LauncherModelInterface(QObject *parent = 0) {}
    virtual ~LauncherModelInterface() {}

    Q_INVOKABLE virtual LauncherItemInterface* get(int index) const = 0;
    Q_INVOKABLE virtual void move(int oldIndex, int newIndex) = 0;

    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles.insert(RoleDesktopFile, "desktopFile");
        roles.insert(RoleName, "name");
        roles.insert(RoleIcon, "icon");
        roles.insert(RoleFavorite, "favorite");
        roles.insert(RoleRunning, "running");
        roles.insert(RoleRecent, "recent");
        return roles;
    }

};

}
}
}

#endif
