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

#ifndef UNITY_SHELL_SCOPES_NAVIGATIONINTERFACE_H
#define UNITY_SHELL_SCOPES_NAVIGATIONINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace scopes
{

/**
 * @brief Object representing department instance, which exposes model(s) with results.
 */
class UNITY_API NavigationInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_ENUMS(Roles)

    /**
     * @brief Id of the navigation.
     */
    Q_PROPERTY(QString navigationId READ navigationId NOTIFY navigationIdChanged)

    /**
     * @brief Canned query that represents this navigation.
     */
    Q_PROPERTY(QString query READ query NOTIFY queryChanged)

    /**
     * @brief Label of the navigation.
     */
    Q_PROPERTY(QString label READ label NOTIFY labelChanged)

    /**
     * @brief Label for "All Button" of the navigation.
     */
    Q_PROPERTY(QString allLabel READ allLabel NOTIFY allLabelChanged)

    /**
     * @brief Parent Id of the navigation.
     */
    Q_PROPERTY(QString parentNavigationId READ parentNavigationId NOTIFY parentNavigationIdChanged)

    /**
     * @brief Canned query that represents parent navigation.
     */
    Q_PROPERTY(QString parentQuery READ parentQuery NOTIFY parentQueryChanged)

    /**
     * @brief Parent label of the navigation.
     */
    Q_PROPERTY(QString parentLabel READ parentLabel NOTIFY parentLabelChanged)

    /**
     * @brief Is the model of the navigation completely loaded?
     */
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)

    /**
     * @brief Is this deparment the root navigation?
     */
    Q_PROPERTY(bool isRoot READ isRoot NOTIFY isRootChanged)

    /**
     * @brief Is this a hidden navigation?
     */
    Q_PROPERTY(bool hidden READ hidden NOTIFY hiddenChanged)

    /**
     * @brief Number of items of the navigation.
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)

protected:
    /// @cond
    explicit NavigationInterface(QObject* parent = 0) : QAbstractListModel(parent) { }
    /// @endcond

public:
    /**
     * @brief The roles supported by this model.
     */
    enum Roles {
        RoleNavigationId,
        RoleQuery,
        RoleLabel,
        RoleHasChildren,
        RoleIsActive
    };

    // @cond
    virtual QString navigationId() const = 0;
    virtual QString query() const = 0;
    virtual QString label() const = 0;
    virtual QString allLabel() const = 0;
    virtual QString parentNavigationId() const = 0;
    virtual QString parentQuery() const = 0;
    virtual QString parentLabel() const = 0;
    virtual bool loaded() const = 0;
    virtual bool isRoot() const = 0;
    virtual bool hidden() const = 0;
    virtual int count() const = 0;
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[RoleNavigationId] = "navigationId";
        roles[RoleQuery] = "query";
        roles[RoleLabel] = "label";
        roles[RoleHasChildren] = "hasChildren";
        roles[RoleIsActive] = "isActive";
        return roles;
    }
    // @endcond

Q_SIGNALS:
    // @cond
    void navigationIdChanged();
    void queryChanged();
    void labelChanged();
    void allLabelChanged();
    void parentNavigationIdChanged();
    void parentQueryChanged();
    void parentLabelChanged();
    void loadedChanged();
    void isRootChanged();
    void hiddenChanged();
    void countChanged();
    // @endcond
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::NavigationInterface*)

#endif
