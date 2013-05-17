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


#include <Mocks/MockSource.h>
#include <Mocks/MockModel.h>
#include <Mocks/MockNotification.h>

#include <unity/shell/notifications/NotificationInterface.h>

using namespace unity::shell::notifications;

MockSource::MockSource(QObject *parent)
    : SourceInterface(parent)
    , m_model(0)
{
}

ModelInterface*
MockSource::model() const
{
    return m_model;
}

void
MockSource::setModel(ModelInterface* model)
{
    MockModel* mockModel = qobject_cast<MockModel*>(model);
    if (m_model != mockModel)
    {
        m_model = mockModel;
        Q_EMIT modelChanged(m_model);
    }
}

void
MockSource::send(QVariantMap data)
{
    MockNotification* notification = new MockNotification(this);
    notification->m_data = data;

    connect(notification, SIGNAL(completed()), SLOT(onCompleted()));

    if(m_model)
    {
        m_model->add(notification);
    }
}

void
MockSource::onCompleted()
{
    sender()->deleteLater();
}
