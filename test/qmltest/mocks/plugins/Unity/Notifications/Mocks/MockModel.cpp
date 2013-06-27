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


#include <Mocks/MockModel.h>
#include <Mocks/MockNotification.h>
#include <Mocks/MockActionModel.h>

#include <unity/shell/notifications/Enums.h>
#include <unity/shell/notifications/SourceInterface.h>
#include <unity/shell/notifications/NotificationInterface.h>

#include <QtCore/QUrl>

using namespace unity::shell::notifications;

MockModel::MockModel(QObject* parent)
    : ModelInterface(parent)
    , m_confirmationPlaceholder(false)
{
    m_roles.insert(Summary, "summary");
    m_roles.insert(Notification, "notification");
    m_roles.insert(Id, "id");
    m_roles.insert(Type, "type");
    m_roles.insert(Urgency, "urgency");
    m_roles.insert(Body, "body");
    m_roles.insert(Value, "value");
    m_roles.insert(Icon, "icon");
    m_roles.insert(SecondaryIcon, "secondaryIcon");
    m_roles.insert(Hints, "hints");
    m_roles.insert(Actions, "actions");
}

int
MockModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_list.count();
}

QVariant
MockModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    MockNotification* notification = m_list.at(index.row());

    if (role == Summary)
    {
        return QVariant("");
    }
    else if (role == Notification)
    {
        return QVariant::fromValue(notification);
    }
    else if (role == Id)
    {
        return QVariant(index.row());
    }
    else if (role == Type)
    {
        if (notification->m_data.contains("type"))
        {
            return notification->m_data["type"];
        }
        else
        {
            return QVariant((int)unity::shell::notifications::Type::TypeEnum::Invalid);
        }
    }
    else if (role == Urgency)
    {
        return QVariant((int)unity::shell::notifications::Urgency::UrgencyEnum::Invalid);
    }
    else if (role == Body)
    {
        return QVariant("");
    }
    else if (role == Value)
    {
        return QVariant(0);
    }
    else if (role == Icon)
    {
        return QVariant::fromValue(QUrl(""));
    }
    else if (role == SecondaryIcon)
    {
        return QVariant::fromValue(QUrl(""));
    }
    else if (role == Hints)
    {
        return QVariant(unity::shell::notifications::Hint::Invalid);
    }
    else if (role == Actions)
    {
        return QVariant::fromValue(notification->m_actions);
    }

    return QVariant();
}

QHash<int, QByteArray>
MockModel::roleNames() const
{
    return m_roles;
}

void
MockModel::setConfirmationPlaceholder(bool confirmationPlaceholder)
{
    if (m_confirmationPlaceholder != confirmationPlaceholder)
    {
        m_confirmationPlaceholder = confirmationPlaceholder;

        if (m_confirmationPlaceholder)
        {
            MockNotification* notification = new MockNotification(this);

            notification->m_data.insert("type", (int)unity::shell::notifications::Type::TypeEnum::Placeholder);
            connect(notification, SIGNAL(dismissed()), SLOT(onDismissed()));

            beginInsertRows(QModelIndex(), 0, 0);
            m_list.insert(0, notification);
            endInsertRows();
        }
        else
        {
            if (m_list.count() > 0
                    && m_list.at(0)->m_data.contains("type")
                    && m_list.at(0)->m_data["type"] == (int)unity::shell::notifications::Type::TypeEnum::Placeholder)
            {
                MockNotification* notification = m_list.at(0);
                beginRemoveRows(QModelIndex(), 0, 0);
                m_list.removeAt(0);
                endRemoveRows();
                notification->deleteLater();
            }
        }

        Q_EMIT confirmationPlaceholderChanged(m_confirmationPlaceholder);
    }
}

void
MockModel::add(MockNotification* notification)
{
    connect(notification, SIGNAL(dismissed()), SLOT(onDismissed()));
    int row = -1;
    if (m_confirmationPlaceholder
            && notification->m_data.contains("type")
            && notification->m_data["type"] == (int)unity::shell::notifications::Type::TypeEnum::Confirmation)
    {
        MockNotification* placeholder = m_list.at(0);
        placeholder->m_data["type"] = (int)unity::shell::notifications::Type::TypeEnum::Confirmation;
        Q_EMIT dataChanged(index(0), index(0));
    }
    else if (m_confirmationPlaceholder)
    {
        row = 1;
    }
    else
    {
        row = 0;
    }

    if (row >= 0)
    {
        beginInsertRows(QModelIndex(), row, row);
        m_list.insert(row, notification);
        endInsertRows();
    }
}

void
MockModel::onDismissed()
{
    MockNotification* notification = qobject_cast<MockNotification*>(sender());
    int row = m_list.indexOf(notification);
    if (row >= 0)
    {
        if (m_confirmationPlaceholder
                && notification->m_data.contains("type")
                && notification->m_data["type"] == (int)unity::shell::notifications::Type::TypeEnum::Confirmation)
        {
            notification->m_data["type"] = (int)unity::shell::notifications::Type::TypeEnum::Placeholder;
            Q_EMIT dataChanged(index(0), index(0));
        }
        else
        {
            beginRemoveRows(QModelIndex(), row, row);
            m_list.removeAt(row);
            endRemoveRows();
        }
    }
}
