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

#ifndef UNITY_SHELL_SCOPES_FILTERSINTERFACE_H
#define UNITY_SHELL_SCOPES_FILTERSINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API FiltersInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)
    Q_ENUMS(FilterType)

public:
    enum Roles {
        RoleFilterId = Qt::UserRole + 1,
        RoleFilterType,
        RoleFilter
    };

    enum FilterType {
        Invalid,
        OptionSelectorFilter,
        RangeInputFilter
        // TODO add remaining filters
    };

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RoleFilterId] = "id";
        roles[RoleFilterType] = "type";
        roles[RoleFilter] = "filter";
        return roles;
    }

protected:
    /// @cond
    explicit FiltersInterface(QObject* parent = 0) : QAbstractListModel(parent) {}
    /// @endcond
};

}

}
}

Q_DECLARE_METATYPE(unity::shell::scopes::FiltersInterface*)

#endif
