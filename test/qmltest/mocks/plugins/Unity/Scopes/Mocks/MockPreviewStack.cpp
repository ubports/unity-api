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
 */

// self
#include "MockPreviewStack.h"

// local
#include "MockPreviewModel.h"

MockPreviewStack::MockPreviewStack(QObject* parent)
 : unity::shell::scopes::PreviewStackInterface(parent)
{
    m_previews << new MockPreviewModel(this);
}

void MockPreviewStack::setWidgetColumnCount(int columnCount)
{
    if (columnCount != 1) {
        qFatal("MockPreviewStack::setWidgetColumnCount != 1 not implemented");
    }
}

int MockPreviewStack::widgetColumnCount() const
{
    return 1;
}

int MockPreviewStack::rowCount(const QModelIndex&) const
{
    return m_previews.size();
}

unity::shell::scopes::PreviewModelInterface* MockPreviewStack::getPreviewModel(int index) const
{
    if (index >= m_previews.size()) {
        return nullptr;
    }

    return m_previews.at(index);
}

QVariant MockPreviewStack::data(const QModelIndex& index, int role) const
{
    switch (role) {
        case RolePreviewModel:
            return QVariant::fromValue(m_previews.at(index.row()));
        default:
            return QVariant();
    }
}
