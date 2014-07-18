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

#ifndef MOCK_SCOPES_H
#define MOCK_SCOPES_H

#include <unity/shell/scopes/ScopesInterface.h>

// Qt
#include <QList>

class MockScope;

class UNITY_API MockScopes : public unity::shell::scopes::ScopesInterface
{
    Q_OBJECT

public:
    MockScopes(QObject *parent = 0);

    Q_INVOKABLE int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    Q_INVOKABLE unity::shell::scopes::ScopeInterface* getScope(int row) const override;
    Q_INVOKABLE unity::shell::scopes::ScopeInterface* getScope(const QString& scope_id) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool loaded() const override;
    unity::shell::scopes::ScopeInterface* overviewScope() const override;

private:
    QList<MockScope*> m_scopes;
    QHash<int, QByteArray> m_roles;
};

#endif // SCOPES_H
