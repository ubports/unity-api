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

#ifndef UNITY_SHELL_APPLICATION_APPLICATIONLISTMODELINTERFACE_H
#define UNITY_SHELL_APPLICATION_APPLICATIONLISTMODELINTERFACE_H

#include <unity/SymbolExport.h>

#include <QtCore/QAbstractListModel>

namespace unity
{
namespace shell
{
namespace application
{

class ApplicationInfoInterface;

/**
 * @brief A list of ApplicationInfo items.
 *
 * This model exposes a list of ApplicationInfo objects in a QML friendly manner.
 */
class UNITY_API ApplicationListModelInterface: public QAbstractListModel
{
   Q_OBJECT

protected:
    /// @cond
    ApplicationListModelInterface(QObject *parent = 0): QAbstractListModel(parent) {
        m_roleNames.insert(RoleAppId, "appId");
        m_roleNames.insert(RoleDesktopFile, "desktopFile");
        m_roleNames.insert(RoleName, "name");
        m_roleNames.insert(RoleComment, "comment");
        m_roleNames.insert(RoleIcon, "icon");
        m_roleNames.insert(RoleExec, "exec");
        m_roleNames.insert(RoleHandle, "handle"); // FIXME: drop this!
        m_roleNames.insert(RoleStage, "stage");
        m_roleNames.insert(RoleState, "state");
        m_roleNames.insert(RoleFullscreen, "fullscreen");
        m_roleNames.insert(RoleFocused, "focused");
        m_roleNames.insert(RoleScreenshot, "screenshot");
    }
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
        RoleComment,
        RoleIcon,
        RoleExec,
        RoleHandle, // TODO: drop this!
        RoleStage,
        RoleState,
        RoleFullscreen,
        RoleFocused,
        RoleScreenshot
    };

    virtual ~LauncherModelInterface() {}

    /**
     * @brief Get an ApplicationInfo item.
     *
     * Note: QML requires the full namespace in the return value.
     *
     * @param index the index of the item to get
     * @returns The item.
     */
    Q_INVOKABLE virtual unity::shell::application::ApplicationInfoInterface *get(int index) const = 0;

    /// @cond
    virtual QHash<int, QByteArray> roleNames() const
    {
        return m_roleNames;
    }
    /// @endcond

protected:
    /// @cond
    QHash<int, QByteArray> m_roleNames;
    /// @endcond

};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_APPLICATIONLISTMODELINTERFACE_H
