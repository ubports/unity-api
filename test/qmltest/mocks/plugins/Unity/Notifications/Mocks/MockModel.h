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


#ifndef MOCKMODEL_H
#define MOCKMODEL_H

#include <unity/SymbolExport.h>

#include <unity/shell/notifications/ModelInterface.h>

#include <QtCore/QList>
#include <QtCore/QVariantMap>

using namespace unity::shell::notifications;

class MockNotification;

class UNITY_API MockModel : public ModelInterface
{
    Q_OBJECT

    Q_ENUMS(RoleEnum)

public:
    MockModel(QObject* parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    bool confirmationPlaceholder() const
    {
        return m_confirmationPlaceholder;
    }

    void setConfirmationPlaceholder(bool confirmationPlaceholder);

    void add(MockNotification* notification);

    enum RoleEnum
    {
        Summary = Qt::DisplayRole,
        Notification = Qt::UserRole,
        Id,
        Type,
        Urgency,
        Body,
        Value,
        Icon,
        SecondaryIcon,
        Hints,
        Actions
    };

private:
    bool m_confirmationPlaceholder;
    QHash<int, QByteArray> m_roles;
    QList<MockNotification*> m_list;

private Q_SLOTS:
    void onDismissed();
};

#endif // MOCKMODEL_H
