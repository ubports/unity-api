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

#ifndef UNITY_SHELL_LAUNCHER_LAUNCHERMODELINTERFACE_H
#define UNITY_SHELL_LAUNCHER_LAUNCHERMODELINTERFACE_H

#include <unity/SymbolExport.h>

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
    /// @cond
    LauncherModelInterface(QObject *parent = 0): QAbstractListModel(parent) {}
    /// @endcond

public:
    /**
     * @brief The Roles supported by the model
     *
     * See LauncherItemInterface properties for details.
     */
    enum Roles {
        RoleAppId = Qt::UserRole,
        RoleDesktopFile,
        RoleName,
        RoleIcon,
        RolePinned,
        RoleRunning,
        RoleRecent,
        RoleProgress,
        RoleCount
    };

    virtual ~LauncherModelInterface() {}

    /**
     * @brief Move an item in the model.
     *
     * @param oldIndex The current (old) index of the item to be moved.
     * @param newIndex The new index where the item should be moved to.
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

    /**
     * @brief Pin an item to the launcher.
     *
     * Recent and running applications will eventually disappear from the model
     * as the application is closed or new recent items appear. Pinning an item
     * to the launcher makes it persist until remove is called on it.
     *
     * @param appId The appId of the item to be pinned.
     * @param index The index where the item should be pinned to. This parameter is optional
     * and if not supplied, the item will be pinned to the current position.
     * Note: If an item is not contained in the launcher yet, calling this without an index
     * will pin the item to the end of the list.
     */
    Q_INVOKABLE virtual void pin(const QString &appId, int index = -1) = 0;

    /**
     * @brief Request removal of an item from the model.
     *
     * Note: The actual removal of the item might be delayed in certain circumstances.
     *
     * @param appId The appId of the item to be removed.
     */
    Q_INVOKABLE virtual void requestRemove(const QString &appId) = 0;


    /**
      * @brief Trigger an action from the QuickList
      *
      * @param appId The appId of the LauncherItem.
      * @param actionIndex The index of the triggered entry in the QuickListModel.
      */
    Q_INVOKABLE virtual void quickListActionInvoked(const QString &appId, int actionIndex) = 0;

    /// @cond
    virtual QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles.insert(RoleAppId, "appId");
        roles.insert(RoleDesktopFile, "desktopFile");
        roles.insert(RoleName, "name");
        roles.insert(RoleIcon, "icon");
        roles.insert(RolePinned, "pinned");
        roles.insert(RoleRunning, "running");
        roles.insert(RoleRecent, "recent");
        roles.insert(RoleProgress, "progress");
        roles.insert(RoleCount, "count");
        return roles;
    }
    /// @endcond

};

} // namespace launcher
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_LAUNCHER_LAUNCHERMODELINTERFACE_H
