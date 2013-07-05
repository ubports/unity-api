/* Copyright (C) 2013 Canonical, Ltd.
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

#ifndef UNITY_SHELL_LAUNCHER_QUICKLISTMODELINTERFACE_H
#define UNITY_SHELL_LAUNCHER_QUICKLISTMODELINTERFACE_H

#include <unity/SymbolExport.h>

#include <QtCore/QAbstractListModel>

namespace unity
{
namespace shell
{
namespace launcher
{

/**
  * @brief A model containing QuickList actions for an application in the launcher.
  *
  * @description The model has the following roles:
  * - RoleLabel: The text entry in the QuickList menu (QString).
  * - RoleIcon: The icon to be shown for this entry (QString).
  * - RoleCheckable: Wether the item is checkable or not (bool).
  * - RoleGroup: A group this item is in. Items in the same group are exclusive (int). -1 for no group.
  */
class UNITY_API QuickListModelInterface: public QAbstractListModel
{
    Q_OBJECT

protected:
    /// @cond
    explicit QuickListModelInterface(QObject *parent = 0) : QAbstractListModel(parent) {}
    /// @endcond
public:
    enum Roles {
        RoleLabel,
        RoleIcon
    };

    /// @cond
    virtual ~QuickListModelInterface() {}
    /// @endcond

    /// @cond
    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles.insert(RoleLabel, "label");
        roles.insert(RoleIcon, "icon");
        return roles;
    }
    /// @endcond

};

} // unity
} // shell
} // launcher

#endif // UNITY_SHELL_LAUNCHER_QUICKLISTMODELINTERFACE_H
