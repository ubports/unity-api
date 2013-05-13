/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
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


#include <Mocks/mockactionmodel.h>
#include <Mocks/mocknotification.h>

#include <QtCore/QVariantList>
#include <QtCore/QVariantMap>

MockActionModel::MockActionModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_notification(qobject_cast<MockNotification*>(parent))
{
    m_roles.insert(Label, "label");
    m_roles.insert(Id, "id");
}

int
MockActionModel::rowCount(const QModelIndex& /* parent */) const
{
    if (m_notification && m_notification->m_data.contains("actions")) {
        QVariantList actions = m_notification->m_data["actions"].value<QVariantList>();
        return actions.count();
    }
    return 0;
}

QVariant
MockActionModel::data(const QModelIndex &index, int role) const
{
    QVariantMap action = m_notification->m_data["actions"].value<QVariantList>()[index.row()].value<QVariantMap>();
    if (role == Label) {
        return action["label"];
    } else if (role == Id) {
        return action["id"];
    } else {
        return QVariant();
    }
}

QHash<int, QByteArray>
MockActionModel::roleNames() const
{
    return m_roles;
}
