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
    MockScope(QString const& id, QString const& name, bool visible, QObject* parent);

    /* getters */
    QString id() const override;
    QString name() const override;
    QString iconHint() const override;
    QString description() const override;
    QString searchHint() const override;
    bool visible() const override;
    QString shortcut() const override;
    bool searchInProgress() const override;
    unity::shell::scopes::CategoriesInterface* categories() const override;
    unity::shell::scopes::SettingsModelInterface* settings() const override;
    QString searchQuery() const override;
    QString noResultsHint() const override;
    QString formFactor() const override;
    bool isActive() const override;
    bool hasDepartments() const override;
    QString currentDepartmentId() const override;
    QVariantMap customizations() const override;

    /* setters */
    void setName(const QString& name);
    void setSearchQuery(const QString& search_query) override;
    void setNoResultsHint(const QString& hint) override;
    void setFormFactor(const QString& form_factor) override;
    void setActive(const bool) override;

    Q_INVOKABLE void activate(QVariant const& result) override;
    Q_INVOKABLE unity::shell::scopes::PreviewStackInterface* preview(QVariant const& result) override;
    Q_INVOKABLE void cancelActivation() override;
    Q_INVOKABLE void closeScope(unity::shell::scopes::ScopeInterface* scope) override;
    Q_INVOKABLE unity::shell::scopes::DepartmentInterface* getDepartment(QString const& departmentId) override;
    Q_INVOKABLE void loadDepartment(QString const& departmentId) override;

protected:
    QString m_id;
    QString m_iconHint;
    QString m_description;
    QString m_name;
    QString m_searchQuery;
    QString m_noResultsHint;
    QString m_formFactor;
    QString m_currentDepartmentId;
    bool m_visible;
    bool m_searching;
    bool m_isActive;
    bool m_hasDepartments;
    QVariantMap m_customizations;

    QString m_previewRendererName;

    unity::shell::scopes::CategoriesInterface* m_categories;
    unity::shell::scopes::SettingsModelInterface* m_settings;
};

#endif
