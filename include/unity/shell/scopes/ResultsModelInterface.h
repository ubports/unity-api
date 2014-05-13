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

#ifndef UNITY_SHELL_SCOPES_RESULTSMODELINTERFACE_H
#define UNITY_SHELL_SCOPES_RESULTSMODELINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

class UNITY_API ResultsModelInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

    Q_PROPERTY(QString categoryId READ categoryId WRITE setCategoryId NOTIFY categoryIdChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Roles {
        RoleUri,
        RoleCategoryId,
        RoleDndUri,
        RoleResult,
        // card components
        RoleTitle,
        RoleArt,
        RoleSubtitle,
        RoleMascot,
        RoleEmblem,
        RoleSummary,
        RoleAttributes,
        RoleBackground
    };

    Q_INVOKABLE virtual QVariant get(int row) const = 0;

    // @cond
    virtual QString categoryId() const = 0;
    virtual int count() const = 0;

    virtual void setCategoryId(QString const& id) = 0;
    // @endcond

Q_SIGNALS:
    // @cond
    void categoryIdChanged();
    void countChanged();
    // @endcond
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::ResultsModelInterface*)

#endif
