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

class UNITY_API ScopesInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)

public:
    enum Roles {
        RoleScope,
        RoleId,
        RoleVisible,
        RoleTitle
    };

    Q_INVOKABLE virtual int rowCount(const QModelIndex& parent = QModelIndex()) const = 0;

    Q_INVOKABLE virtual QVariant get(int row) const = 0;
    Q_INVOKABLE virtual QVariant get(QString const& scopeId) const = 0;

    // @cond
    virtual bool loaded() const = 0;
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
