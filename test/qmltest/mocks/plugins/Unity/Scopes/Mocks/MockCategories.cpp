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
 *
 * Author: Nick Dedekind <nick.dedekind@canonical.com>
 */

// self
#include "MockCategories.h"

#include "MockResultsModel.h"

MockCategories::MockCategories(int category_count, QObject* parent)
    : unity::shell::scopes::CategoriesInterface(parent)
    , m_category_count(category_count)
{
}

int MockCategories::rowCount(const QModelIndex& /*parent*/) const
{
    return m_category_count;
}

bool MockCategories::overrideCategoryJson(QString const& , QString const& )
{
    qFatal("Using un-implemented MockCategories::overrideCategoryJson");
    return false;
}

QVariant
MockCategories::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    MockResultsModel *resultsModel = m_resultsModels[index.row()];
    if (!resultsModel) {
        resultsModel = new MockResultsModel(15, index.row());
        m_resultsModels[index.row()] = resultsModel;
    }
    switch (role) {
        case RoleCategoryId:
            return QString("%1").arg(index.row());
        case RoleName:
            return QString("Category %1").arg(index.row());
        case RoleIcon:
            return "gtk-apply";
        case RoleRawRendererTemplate:
            return QString();
        case RoleRenderer:
        {
            QVariantMap map;
            map["category-layout"] = index.row() % 2 == 0 ? "grid" : "carousel";
            map["card-size"] = "small";
            return map;
        }
        case RoleComponents:
        {
            QVariantMap map, artMap;
            artMap["aspect-ratio"] = "1.0";
            artMap["field"] = "art";
            map["art"] = artMap;
            map["title"] = "HOLA";
            return map;
        }
        case RoleHeaderLink:
            return QString();
        case RoleResults:
            return QVariant::fromValue(resultsModel);
        case RoleCount:
            return resultsModel->rowCount();
        default:
            qFatal("Using un-implemented Categories role");
            return QVariant();
    }
}
