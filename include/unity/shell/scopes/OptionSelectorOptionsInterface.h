/*
 * Copyright (C) 2015 Canonical, Ltd.
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

#ifndef OPTIONSELECTOROPTIONSINTERFACE_H
#define OPTIONSELECTOROPTIONSINTERFACE_H

#include <unity/SymbolExport.h>
#include <QAbstractListModel>
#include <unity/scopes/FilterOption.h>
#include <unity/scopes/FilterState.h>
#include <list>

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API OptionSelectorOptionsInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(OptionRoles)

public:
    enum Roles {
        RoleOptionId = Qt::UserRole + 1,
        RoleOptionLabel,
        RoleOptionChecked
    };

    Q_INVOKABLE virtual void setChecked(int index, bool checked) = 0;

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RoleOptionId] = "id";
        roles[RoleOptionLabel] = "label";
        roles[RoleOptionChecked] = "checked";
        return roles;
    }

protected:
    /// @cond
    explicit OptionSelectorOptionsInterface(QObject* parent = 0) : QAbstractListModel(parent) {}
    /// @endcond
};

}

}
}

Q_DECLARE_METATYPE(unity::shell::scopes::OptionSelectorOptionsInterface*)

#endif
