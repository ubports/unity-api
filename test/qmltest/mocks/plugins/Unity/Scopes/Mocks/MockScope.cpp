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
#include "MockDepartment.h"
#include "MockSettingsModel.h"

MockScope::MockScope(QObject* parent) : MockScope(QString(), QString(), parent)
{
}

MockScope::MockScope(QString const& id, QString const& name, QObject* parent)
    : unity::shell::scopes::ScopeInterface(parent)
    , m_id(id)
    , m_name(name)
    , m_favorite(false)
    , m_searching(false)
    , m_isActive(false)
    , m_previewRendererName("preview-generic")
    , m_categories(new MockCategories(20, this))
    , m_settings(new MockSettingsModel(this))
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

QString MockScope::currentNavigationId() const {
    return m_currentDepartmentId;
}

QString MockScope::currentAltNavigationId() const {
    return m_currentAltDepartmentId;
}

bool MockScope::searchInProgress() const {
    return m_searching;
}

unity::shell::scopes::CategoriesInterface* MockScope::categories() const {
    return m_categories;
}

unity::shell::scopes::SettingsModelInterface* MockScope::settings() const {
    return m_settings;
}

QString MockScope::noResultsHint() const {
    return m_noResultsHint;
}

QString MockScope::formFactor() const {
    return m_formFactor;
}

bool MockScope::favorite() const {
    return m_favorite;
}

bool MockScope::isActive() const {
    return m_isActive;
}

bool MockScope::hasNavigation() const {
    return m_hasNavigation;
}

bool MockScope::hasAltNavigation() const {
    return m_hasAltNavigation;
}

QVariantMap MockScope::customizations() const {
    return m_customizations;
}

unity::shell::scopes::ScopeInterface::Status MockScope::status() const {
    return ScopeInterface::Status::Okay;
}

void MockScope::setName(const QString &str) {
    if (str != m_name) {
        m_name = str;
        Q_EMIT nameChanged();
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
        Q_EMIT isActiveChanged();
    }
}

void MockScope::setFavorite(const bool value) {
    if (value != m_favorite) {
        m_favorite = value;
        Q_EMIT favoriteChanged();
    }
}

void MockScope::setNoResultsHint(const QString& str) {
    if (str != m_noResultsHint) {
        m_noResultsHint = str;
        Q_EMIT noResultsHintChanged();
    }
}

void MockScope::activate(QVariant const& result, QString const& categoryId)
{
    Q_UNUSED(result);
    Q_UNUSED(categoryId);
}

void MockScope::activateAction(QVariant const& result, QString const& categoryId, QString const& actionId)
{
    Q_UNUSED(result);
    Q_UNUSED(categoryId);
    Q_UNUSED(actionId);
}

unity::shell::scopes::PreviewStackInterface* MockScope::preview(QVariant const& result, QString const& categoryId)
{
    Q_UNUSED(result);
    Q_UNUSED(categoryId);

    // This probably leaks, do we don't care
    // it's a  test after all
    return new MockPreviewStack;
}

unity::shell::scopes::NavigationInterface* MockScope::getNavigation(QString const& navigationId)
{
    Q_UNUSED(navigationId);

    return new MockDepartment();
}

unity::shell::scopes::NavigationInterface* MockScope::getAltNavigation(QString const& navigationId)
{
    Q_UNUSED(navigationId);

    return new MockDepartment();
}

void MockScope::setNavigationState(QString const& navId, bool altNavigation)
{
    Q_UNUSED(navId);
    Q_UNUSED(altNavigation);
}

void MockScope::cancelActivation()
{
}

void MockScope::closeScope(unity::shell::scopes::ScopeInterface* /*scope*/)
{
    qFatal("MockScope::closeScope is not implemented");
}

void MockScope::performQuery(QString const& cannedQuery)
{
    Q_UNUSED(cannedQuery);
}

void MockScope::refresh()
{
}
