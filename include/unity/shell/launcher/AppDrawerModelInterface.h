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

#pragma once

#include <QAbstractListModel>

namespace unity {
namespace shell {
namespace launcher {

class AppDrawerModelInterface: public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)
public:
    enum Roles {
        RoleAppId,
        RoleName,
        RoleIcon,
        RoleUsage
    };

    AppDrawerModelInterface(QObject* parent = nullptr): QAbstractListModel(parent) {}
    virtual ~AppDrawerModelInterface() {}

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles.insert(RoleAppId, "appId");
        roles.insert(RoleName, "name");
        roles.insert(RoleIcon, "icon");
        roles.insert(RoleUsage, "usage");
        return roles;
    }
};

}
}
}
