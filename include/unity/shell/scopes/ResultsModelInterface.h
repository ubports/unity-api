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

#ifndef UNITY_SHELL_SCOPES_RESULTSMODELINTERFACE_H
#define UNITY_SHELL_SCOPES_RESULTSMODELINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

/**
 * @brief A model of scope results for a particular category.
 */
class UNITY_API ResultsModelInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

    /**
     * @brief Id of associated category.
     */
    Q_PROPERTY(QString categoryId READ categoryId WRITE setCategoryId NOTIFY categoryIdChanged)

    /**
     * @brief Number of items in the model.
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)

protected:
    /// @cond
    explicit ResultsModelInterface(QObject* parent = 0) : QAbstractListModel(parent) { }
    /// @endcond

public:
    /**
     * @brief The Roles supported by this model.
     */
    enum Roles {
        RoleUri,
        RoleCategoryId,
        RoleDndUri,
        RoleResult,
        // card components
        RoleTitle,
        RoleArt,
        RoleSubtitle,
        RoleMascot,
        RoleEmblem,
        RoleSummary,
        RoleAttributes,
        RoleBackground,
        RoleOverlayColor,
        RoleQuickPreviewData ///< Data for UI quick previewing. In case of audio should contain uri and duration
    };

    // @cond
    virtual QString categoryId() const = 0;
    virtual int count() const = 0;

    virtual void setCategoryId(QString const& id) = 0;
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RoleUri] = "uri";
        roles[RoleCategoryId] = "categoryId";
        roles[RoleDndUri] = "dndUri";
        roles[RoleQuickPreviewData] = "quickPreviewData";
        roles[RoleResult] = "result";
        roles[RoleTitle] = "title";
        roles[RoleArt] = "art";
        roles[RoleSubtitle] = "subtitle";
        roles[RoleMascot] = "mascot";
        roles[RoleEmblem] = "emblem";
        roles[RoleSummary] = "summary";
        roles[RoleAttributes] = "attributes";
        roles[RoleBackground] = "background";
        roles[RoleOverlayColor] = "overlayColor";
        return roles;
    }

    // @endcond

Q_SIGNALS:
    // @cond
    void categoryIdChanged();
    void countChanged();
    // @endcond
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::ResultsModelInterface*)

#endif
