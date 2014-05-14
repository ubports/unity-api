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
 *
 */

// Self
#include "MockScopes.h"

#include "MockScope.h"

MockScopes::MockScopes(QObject *parent)
 : unity::shell::scopes::ScopesInterface(parent)
{
    m_scopes << new MockScope("MockScope1", "People", true, this);
    m_scopes << new MockScope("MockScope2", "Music", false, this);
    m_scopes << new MockScope("MockScope3", "Apps", true, this);
    m_scopes << new MockScope("MockScope4", "Videos", true, this);
}

bool MockScopes::loaded() const
{
    return true;
}

int MockScopes::rowCount(const QModelIndex&) const
{
    return m_scopes.count();
}

QVariant MockScopes::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_scopes.size()) {
        return QVariant();
    }

    MockScope* scope = m_scopes.at(index.row());

    if (role == MockScopes::RoleScope) {
        return QVariant::fromValue(scope);
    } else if (role == MockScopes::RoleId) {
        return QVariant::fromValue(scope->id());
    } else if (role == MockScopes::RoleVisible) {
        return QVariant::fromValue(scope->visible());
    } else if (role == MockScopes::RoleTitle) {
        return QVariant::fromValue(scope->name());
    } else {
        return QVariant();
    }
}

QVariant MockScopes::get(int row) const
{
    return data(QAbstractListModel::index(row), 0);
}

QVariant MockScopes::get(QString const&) const
{
    // Unimplemented
    return QVariant();
}
