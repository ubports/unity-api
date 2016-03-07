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

#ifndef MOCKSCOPE_H
#define MOCKSCOPE_H

#include <unity/shell/scopes/ScopeInterface.h>

class UNITY_API MockScope : public unity::shell::scopes::ScopeInterface
{
    Q_OBJECT

public:
    MockScope(QObject* parent = 0);
    MockScope(QString const& id, QString const& name, QObject* parent);

    /* getters */
    QString id() const override;
    QString name() const override;
    QString iconHint() const override;
    QString description() const override;
    QString searchHint() const override;
    bool favorite() const override;
    QString shortcut() const override;
    bool searchInProgress() const override;
    bool activationInProgress() const override;
    unity::shell::scopes::CategoriesInterface* categories() const override;
    unity::shell::scopes::SettingsModelInterface* settings() const override;
    QString searchQuery() const override;
    QString noResultsHint() const override;
    QString formFactor() const override;
    bool isActive() const override;
    bool hasNavigation() const override;
    QString currentNavigationId() const override;
    bool hasAltNavigation() const override;
    QString currentAltNavigationId() const override;
    QVariantMap customizations() const override;
    Status status() const override;

    /* setters */
    void setName(const QString& name);
    void setSearchQuery(const QString& search_query) override;
    void setNoResultsHint(const QString& hint) override;
    void setFormFactor(const QString& form_factor) override;
    void setActive(const bool) override;
    void setFavorite(const bool) override;

    Q_INVOKABLE void activate(QVariant const& result, QString const& categoryId) override;
    Q_INVOKABLE void activateAction(QVariant const& result, QString const& categoryId, QString const& actionId) override;
    Q_INVOKABLE unity::shell::scopes::PreviewModelInterface* preview(QVariant const& result, QString const& categoryId) override;
    Q_INVOKABLE void cancelActivation() override;
    Q_INVOKABLE void closeScope(unity::shell::scopes::ScopeInterface* scope) override;
    Q_INVOKABLE unity::shell::scopes::NavigationInterface* getNavigation(QString const& departmentId) override;
    Q_INVOKABLE unity::shell::scopes::NavigationInterface* getAltNavigation(QString const& departmentId) override;
    Q_INVOKABLE void setNavigationState(QString const& navId, bool altNavigation) override;
    Q_INVOKABLE void performQuery(QString const& cannedQuery) override;
    Q_INVOKABLE void refresh() override;

protected:
    QString m_id;
    QString m_iconHint;
    QString m_description;
    QString m_name;
    QString m_searchQuery;
    QString m_noResultsHint;
    QString m_formFactor;
    QString m_currentDepartmentId;
    QString m_currentAltDepartmentId;
    bool m_favorite;
    bool m_searching;
    bool m_isActive;
    bool m_hasNavigation;
    bool m_hasAltNavigation;
    QVariantMap m_customizations;

    QString m_previewRendererName;

    unity::shell::scopes::CategoriesInterface* m_categories;
    unity::shell::scopes::SettingsModelInterface* m_settings;
};

#endif
