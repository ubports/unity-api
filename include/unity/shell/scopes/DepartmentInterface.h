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

#ifndef UNITY_SHELL_SCOPES_DEPARTMENTINTERFACE_H
#define UNITY_SHELL_SCOPES_DEPARTMENTINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

/**
 * @brief A list of PreviewWidgetModelInterface instances.
 *
 * This model exposes a number of PreviewWidgetModelInterface instances based on
 * the value of widgetColumnCount property.
 */
class UNITY_API DepartmentInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

    Q_PROPERTY(QString departmentId READ departmentId NOTIFY departmentIdChanged)
    Q_PROPERTY(QString label READ label NOTIFY labelChanged)
    Q_PROPERTY(QString allLabel READ allLabel NOTIFY allLabelChanged)
    Q_PROPERTY(QString parentId READ parentId NOTIFY parentIdChanged)
    Q_PROPERTY(QString parentLabel READ parentLabel NOTIFY parentLabelChanged)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)
    Q_PROPERTY(bool isRoot READ isRoot NOTIFY isRootChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


    /**
     * @brief Boolean specifying whether loading this preview finished.
     */
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)

protected:
    /// @cond
    explicit DepartmentInterface(QObject* parent = 0) : QAbstractListModel(parent) { }
    /// @endcond

public:
    /**
     * @brief The roles supported by this model.
     */
    enum Roles {
        RoleDepartmentId,
        RoleLabel,
        RoleHasChildren,
        RoleIsActive
    };

    // @cond
    virtual QString departmentId() const = 0;
    virtual QString label() const = 0;
    virtual QString allLabel() const = 0;
    virtual QString parentId() const = 0;
    virtual QString parentLabel() const = 0;
    virtual bool loaded() const = 0;
    virtual bool isRoot() const = 0;
    virtual int count() const = 0;
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RoleDepartmentId] = "departmentId";
        roles[RoleLabel] = "label";
        roles[RoleHasChildren] = "hasChildren";
        roles[RoleIsActive] = "isActive";
        return roles;
    }
    // @endcond

Q_SIGNALS:
    // @cond
    void departmentIdChanged();
    void labelChanged();
    void allLabelChanged();
    void parentIdChanged();
    void parentLabelChanged();
    void loadedChanged();
    void isRootChanged();
    void countChanged();
    // @endcond
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::DepartmentInterface*)

#endif
