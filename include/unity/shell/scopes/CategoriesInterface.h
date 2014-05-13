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

#ifndef UNITY_SHELL_SCOPES_CATEGORESINTERFACE_H
#define UNITY_SHELL_SCOPES_CATEGORESINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API CategoriesInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

public:
    enum Roles {
        RoleCategoryId,
        RoleName,
        RoleIcon,
        RoleRawRendererTemplate,
        RoleRenderer,
        RoleComponents,
        RoleProgressSource, // maybe
        RoleResults,
        RoleCount
    };

    Q_INVOKABLE virtual bool overrideCategoryJson(QString const& categoryId, QString const& json) = 0;
    Q_INVOKABLE virtual void addSpecialCategory(QString const& categoryId, QString const& name, QString const& icon, QString const& rawTemplate, QObject* countObject) = 0;
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::CategoriesInterface*)

#endif
