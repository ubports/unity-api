/*
 * Copyright (C) 2014 Canonical, Ltd.
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

#ifndef UNITY_SHELL_SCOPES_SCOPESINTERFACE_H
#define UNITY_SHELL_SCOPES_SCOPESINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

/**
 * @brief A list of scopes to display in the UI.
 *
 * This model exposes information about scopes that should be shown by the dash.
 */
class UNITY_API ScopesInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

    /**
     * @brief Boolean indicating whether asynchronous populating of the model finished.
     */
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)

protected:
    /// @cond
    explicit ScopesInterface(QObject* parent = 0) : QAbstractListModel(parent) { }
    /// @endcond

public:
    /**
     * @brief Roles supported by the model.
     */
    enum Roles {
        RoleScope,
        RoleId,
        RoleVisible,
        RoleTitle
    };

    /**
     * @brief Number of rows in the model.
     */
    Q_INVOKABLE virtual int rowCount(const QModelIndex& parent = QModelIndex()) const = 0;

    /**
     * @brief Get ScopeInterface instance associated with a row.
     *
     * Returns ScopeInterface instance associated with a row or a null variant when
     * supplied with incorrect index.
     */
    Q_INVOKABLE virtual QVariant get(int row) const = 0;

    /**
     * @brief Get ScopeInterface instance by scope id.
     *
     * Returns ScopeInterface instance which with the supplied scope id or a null
     * variant.
     */
    Q_INVOKABLE virtual QVariant get(QString const& scopeId) const = 0;

    // @cond
    virtual bool loaded() const = 0;
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RoleScope] = "scope";
        roles[RoleId] = "id";
        roles[RoleVisible] = "visible";
        roles[RoleTitle] = "title";
        return roles;
    }
    // @endcond

Q_SIGNALS:
    // @cond
    void loadedChanged(bool loaded);
    // @endcond
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::ScopesInterface*)

#endif
