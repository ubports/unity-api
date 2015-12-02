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

#ifndef UNITY_SHELL_SCOPES_VALUESLIDERVALUESINTERFACE_H
#define UNITY_SHELL_SCOPES_VALUESLIDERVALUESINTERFACE_H

#include <unity/SymbolExport.h>
#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API ValueSliderValuesInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(SliderValueRoles)

public:
    enum Roles {
        RoleValue = Qt::UserRole + 1,
        RoleLabel
    };

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RoleValue] = "value";
        roles[RoleLabel] = "label";
        return roles;
    }

protected:
    /// @cond
    explicit ValueSliderValuesInterface(QObject* parent = 0) : QAbstractListModel(parent) {}
    /// @endcond
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::ValueSliderValuesInterface*)

#endif
