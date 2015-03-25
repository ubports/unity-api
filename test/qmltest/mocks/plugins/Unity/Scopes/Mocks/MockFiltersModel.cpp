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

#include "MockFiltersModel.h"
#include "MockOptionSelectorFilter.h"

MockFiltersModel::MockFiltersModel(unity::shell::scopes::ScopeInterface *parent)
    : unity::shell::scopes::FiltersInterface(parent)
{
    QSharedPointer<MockOptionSelectorFilter> f(new MockOptionSelectorFilter("f1", "Filter 1", false, this));
    m_filters.append(f);
}

QVariant MockFiltersModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= 0 && index.row() < m_filters.count())
    {
        auto filter = m_filters.at(index.row());
        switch (role)
        {
            case Qt::DisplayRole:
            case unity::shell::scopes::FiltersInterface::RoleFilterId:
                return QVariant(filter->id());
            case unity::shell::scopes::FiltersInterface::RoleFilterType:
                return QVariant(static_cast<int>(filter->filterType()));
            case unity::shell::scopes::FiltersInterface::RoleFilter:
                return QVariant::fromValue(filter.data());
            default:
                return QVariant();
        }
    }
    return QVariant();
}

int MockFiltersModel::rowCount(const QModelIndex&) const
{
    return m_filters.count();
}
