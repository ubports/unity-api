/*
 * Copyright (C) 2014 Canonical, Ltd.
 *
 * Authors:
 *  Michał Sawicz <michal.sawicz@canonical.com>
 *  Michal Hruby <michal.hruby@canonical.com>
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

class UNITY_API PreviewWidgetModelInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

public:
    enum Roles {
        RoleWidgetId,
        RoleType,
        RoleProperties
    };
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::PreviewWidgetModelInterface*)

#endif
