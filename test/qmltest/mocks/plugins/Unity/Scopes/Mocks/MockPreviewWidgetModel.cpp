/*
 * Copyright (C) 2014 Canonical, Ltd.
 *
 * Authors:
 *  Michał Sawicz <michal.sawicz@canonical.com>
 *  Michal Hruby <michal.hruby@canonical.com>
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
#include "MockPreviewWidgetModel.h"

// Qt
#include <QVariantMap>

struct MockPreviewData
{
    QString id;
    QString type;
    QVariantMap data;

    MockPreviewData(QString const& id_, QString const& type_, QVariantMap const& data_): id(id_), type(type_), data(data_)
    {
    }
};

MockPreviewWidgetModel::MockPreviewWidgetModel(QObject* parent)
{
    setParent(parent);

    for (int i = 0; i <= 20; i++) {
        QVariantMap attributes;
        attributes["text"] = QVariant::fromValue(QString("Widget %1").arg(i));
        attributes["title"] = QVariant::fromValue(QString("Title %1").arg(i));
        MockPreviewData* preview_data = new MockPreviewData(QString("widget-%1").arg(i), QString("text"), attributes);
        m_previewWidgets.append(QSharedPointer<MockPreviewData>(preview_data));
    }
}

int MockPreviewWidgetModel::rowCount(const QModelIndex&) const
{
    return m_previewWidgets.size();
}

QVariant MockPreviewWidgetModel::data(const QModelIndex& index, int role) const
{
    auto widget_data = m_previewWidgets.at(index.row());
    switch (role) {
        case RoleWidgetId:
            return widget_data->id;
        case RoleType:
            return widget_data->type;
        case RoleProperties:
            return widget_data->data;
        default:
            return QVariant();
    }
}
