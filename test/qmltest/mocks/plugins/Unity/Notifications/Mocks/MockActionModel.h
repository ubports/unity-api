/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Michał Sawicz <michal.sawicz@canonical.com>
 */


#ifndef MOCKACTIONMODEL_H
#define MOCKACTIONMODEL_H

#include <unity/SymbolExport.h>

#include <QtCore/QAbstractListModel>

class MockNotification;

class UNITY_API MockActionModel : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(RoleEnum)
public:
    explicit MockActionModel(QObject *parent = 0);

    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    enum RoleEnum
    {
        Label = Qt::DisplayRole,
        Id = Qt::UserRole
    };

private:
    QHash<int, QByteArray> m_roles;
    MockNotification* m_notification;
};

Q_DECLARE_METATYPE(MockActionModel*)

#endif // MOCKACTIONMODEL_H
