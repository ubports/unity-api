/*
 * Copyright (C) 2015 Canonical, Ltd.
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

#include "MockSelectorOptions.h"

MockSelectorOptions::MockSelectorOptions(int num, QObject *parent)
    : unity::shell::scopes::OptionSelectorOptionsInterface(parent),
    m_numOfOptions(num)
{
}

QVariant MockSelectorOptions::data(const QModelIndex& index, int role) const
{
    if (index.row() >= 0 && index.row() < m_numOfOptions)
    {
        switch (role)
        {
            case unity::shell::scopes::OptionSelectorOptionsInterface::RoleOptionId:
                return QVariant(QString("option") + QString::number(index.row()));
            case Qt::DisplayRole:
            case unity::shell::scopes::OptionSelectorOptionsInterface::RoleOptionLabel:
                return QVariant(QString("Option") + QString::number(index.row()));
            case unity::shell::scopes::OptionSelectorOptionsInterface::RoleOptionChecked:
                return QVariant(false);
            default:
                return QVariant();
        }
    }
    return QVariant();
}

int MockSelectorOptions::rowCount(const QModelIndex&) const
{
    return m_numOfOptions;
}

void MockSelectorOptions::setChecked(int, bool)
{
    qFatal("Using un-implemented setChecked() method");
}
