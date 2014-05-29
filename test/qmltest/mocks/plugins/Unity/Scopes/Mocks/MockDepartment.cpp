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

// self
#include "MockDepartment.h"

MockDepartment::MockDepartment(QObject* parent)
 : unity::shell::scopes::DepartmentInterface(parent)
{
}

QString MockDepartment::departmentId() const
{
    return "root";
}

QString MockDepartment::label() const
{
    return "All Departments";
}

QString MockDepartment::allLabel() const
{
    return "All Departments";
}

QString MockDepartment::parentId() const
{
    return QString();
}

QString MockDepartment::parentLabel() const
{
    return QString();
}

bool MockDepartment::loaded() const
{
    return true;
}

bool MockDepartment::isRoot() const
{
    return true;
}

int MockDepartment::count() const
{
    return rowCount();
}

int MockDepartment::rowCount(const QModelIndex&) const
{
    return 1;
}

QVariant MockDepartment::data(const QModelIndex& /*index*/, int role) const
{
    switch (role) {
        case RoleDepartmentId:
            return "child";
        case RoleLabel:
            return "Child Clothes";
        case RoleHasChildren:
            return true;
        case RoleIsActive:
            return false;
        default:
            return QVariant();
    }
}
