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

#ifndef UNITY_SHELL_SCOPES_PREVIEWWIDGETMODELINTERFACE_H
#define UNITY_SHELL_SCOPES_PREVIEWWIDGETMODELINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

/**
 * @brief A list of widgets in a preview.
 *
 * This model exposes all the widgets that belong to a particular column in a preview.
 */
class UNITY_API PreviewWidgetModelInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

protected:
    /// @cond
    explicit PreviewWidgetModelInterface(QObject* parent = 0) : QAbstractListModel(parent) { }
    /// @endcond

public:
    /**
     * @brief The roles supported by this model.
     */
    enum Roles {
        RoleWidgetId,
        RoleType,
        RoleProperties
    };

    // @cond
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RoleWidgetId] = "widgetId";
        roles[RoleType] = "type";
        roles[RoleProperties] = "properties";
        return roles;
    }
    // @endcond
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::PreviewWidgetModelInterface*)

#endif
