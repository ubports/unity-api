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
    m_scopes << new MockScope("MockScope1", "People", this);
    m_scopes << new MockScope("MockScope2", "Music", this);
    m_scopes << new MockScope("MockScope3", "Apps", this);
    m_scopes << new MockScope("MockScope4", "Videos", this);
}

bool MockScopes::loaded() const
{
    return true;
}

unity::shell::scopes::ScopeInterface* MockScopes::overviewScope() const
{
    return nullptr;
}

int MockScopes::rowCount(const QModelIndex&) const
{
    return m_scopes.count();
}

int MockScopes::count() const
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
    } else if (role == MockScopes::RoleTitle) {
        return QVariant::fromValue(scope->name());
    } else {
        return QVariant();
    }
}

unity::shell::scopes::ScopeInterface* MockScopes::getScope(int row) const
{
    if (row < 0 ||  row >= m_scopes.size()) {
        return nullptr;
    }

    return m_scopes[row];
}

unity::shell::scopes::ScopeInterface* MockScopes::getScope(QString const&) const
{
    // Unimplemented
    return nullptr;
}

void MockScopes::setFavorite(QString const&, bool)
{
    // Unimplemented
}

void MockScopes::moveFavoriteTo(QString const&, int)
{
    // Unimplemented
}
