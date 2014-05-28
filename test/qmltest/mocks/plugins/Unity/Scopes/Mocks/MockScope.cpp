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

#include "MockScope.h"
#include "MockCategories.h"
#include "MockPreviewStack.h"

MockScope::MockScope(QObject* parent) : MockScope(QString(), QString(), false, parent)
{
}

MockScope::MockScope(QString const& id, QString const& name, bool visible, QObject* parent)
    : unity::shell::scopes::ScopeInterface(parent)
    , m_id(id)
    , m_name(name)
    , m_visible(visible)
    , m_searching(false)
    , m_isActive(false)
    , m_previewRendererName("preview-generic")
    , m_categories(new MockCategories(20, this))
{
}

QString MockScope::id() const {
    return m_id;
}

QString MockScope::name() const {
    return m_name;
}

QString MockScope::searchQuery() const {
    return m_searchQuery;
}

QString MockScope::iconHint() const {
    return m_iconHint;
}

QString MockScope::description() const {
    return m_description;
}

QString MockScope::searchHint() const {
    return QString("");
}

QString MockScope::shortcut() const {
    return QString("");
}

QString MockScope::currentDepartment const {
    return m_currentDepartment;
}

bool MockScope::searchInProgress() const {
    return m_searching;
}

unity::shell::scopes::CategoriesInterface* MockScope::categories() const {
    return m_categories;
}

QString MockScope::noResultsHint() const {
    return m_noResultsHint;
}

QString MockScope::formFactor() const {
    return m_formFactor;
}

bool MockScope::visible() const {
    return m_visible;
}

bool MockScope::isActive() const {
    return m_isActive;
}

bool MockScope::hasDepartments() const {
    return m_hasDepartments;
}

void MockScope::setName(const QString &str) {
    if (str != m_name) {
        m_name = str;
        Q_EMIT nameChanged(m_name);
    }
}

void MockScope::setSearchQuery(const QString &str) {
    if (str != m_searchQuery) {
        m_searchQuery = str;
        Q_EMIT searchQueryChanged();
    }
}

void MockScope::setFormFactor(const QString &str) {
    if (str != m_formFactor) {
        m_formFactor = str;
        Q_EMIT formFactorChanged();
    }
}

void MockScope::setActive(const bool active) {
    if (active != m_isActive) {
        m_isActive = active;
        Q_EMIT isActiveChanged(active);
    }
}

void MockScope::setNoResultsHint(const QString& str) {
    if (str != m_noResultsHint) {
        m_noResultsHint = str;
        Q_EMIT noResultsHintChanged();
    }
}

void MockScope::activate(QVariant const& result)
{
    Q_UNUSED(result);
}

unity::shell::scopes::PreviewStackInterface* MockScope::preview(QVariant const& result)
{
    Q_UNUSED(result);

    // This probably leaks, do we don't care
    // it's a  test after all
    return new MockPreviewStack;
}

unity::shell::scopes::DepartmentInterface* MockScope::getDepartment(QString const& departmentId)
{
    return nullptr;
}

void MockScope::loadDepartment(QString const& departmentId)
{
}

void MockScope::cancelActivation()
{
}

void MockScope::closeScope(unity::shell::scopes::ScopeInterface* /*scope*/)
{
    qFatal("MockScope::closeScope is not implemented");
}
