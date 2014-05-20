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
#include "MockPreviewModel.h"

// local
#include "MockPreviewWidgetModel.h"

// Qt
#include <QDebug>

MockPreviewModel::MockPreviewModel(QObject* parent)
 : unity::shell::scopes::PreviewModelInterface(parent)
{
    // we have one column by default
    MockPreviewWidgetModel* columnModel = new MockPreviewWidgetModel(this);
    m_previewWidgetModels.append(columnModel);
}

void MockPreviewModel::setWidgetColumnCount(int count)
{
    if (count != 1) {
        qWarning("MockPreviewModel::setWidgetColumnCount != 1 not implemented");
    }
}

int MockPreviewModel::widgetColumnCount() const
{
    return 1;
}

bool MockPreviewModel::loaded() const
{
    return true;
}

bool MockPreviewModel::processingAction() const
{
    return false;
}

int MockPreviewModel::rowCount(const QModelIndex&) const
{
    return m_previewWidgetModels.size();
}

QVariant MockPreviewModel::data(const QModelIndex& index, int role) const
{
    switch (role) {
        case RoleColumnModel:
            return QVariant::fromValue(m_previewWidgetModels.at(index.row()));
        default:
            return QVariant();
    }
}
