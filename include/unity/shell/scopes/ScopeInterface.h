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

#ifndef UNITY_SHELL_SCOPES_SCOPEINTERFACE_H
#define UNITY_SHELL_SCOPES_SCOPEINTERFACE_H

#include <unity/SymbolExport.h>

#include <QObject>
#include <QVariantMap>

namespace unity
{
namespace shell
{
namespace scopes
{

class CategoriesInterface;
class PreviewStackInterface;
class DepartmentInterface;

/**
 * @brief Object representing scope instance, which exposes model(s) with results.
 */
class UNITY_API ScopeInterface : public QObject
{
    Q_OBJECT

    /**
     * @brief Id of the scope.
     */
    Q_PROPERTY(QString id READ id NOTIFY idChanged)

    /**
     * @brief Display name of the scope.
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

    /**
     * @brief URI to scope's icon.
     */
    Q_PROPERTY(QString iconHint READ iconHint NOTIFY iconHintChanged)

    /**
     * @brief Description of the scope.
     */
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)

    /**
     * @brief Hint to display in the search field.
     */
    Q_PROPERTY(QString searchHint READ searchHint NOTIFY searchHintChanged)

    /**
     * @brief Boolean specifying whether a search is currently running.
     */
    Q_PROPERTY(bool searchInProgress READ searchInProgress NOTIFY searchInProgressChanged)

    /**
     * @brief Boolean specifying whether the scope should be visible.
     */
    Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)

    /**
     * @brief Keyboard shortcut used to summon the scope.
     */
    Q_PROPERTY(QString shortcut READ shortcut NOTIFY shortcutChanged)

    /**
     * @brief Categories model for scope's results.
     */
    Q_PROPERTY(unity::shell::scopes::CategoriesInterface* categories READ categories NOTIFY categoriesChanged)

    /**
     * @brief Current search query.
     *
     * Writing to this property issues a new search to the scope.
     */
    Q_PROPERTY(QString searchQuery READ searchQuery WRITE setSearchQuery NOTIFY searchQueryChanged)

    /**
     * @brief Message to display when there are no results after a search.
     */
    Q_PROPERTY(QString noResultsHint READ noResultsHint WRITE setNoResultsHint NOTIFY noResultsHintChanged)

    /**
     * @brief Form factor which is sent with search queries.
     *
     * Form factor is one of scope inputs and be used by it to fine-tune the results.
     *
     * TODO Document the supported for factors
     */
    Q_PROPERTY(QString formFactor READ formFactor WRITE setFormFactor NOTIFY formFactorChanged)

    /**
     * @brief Boolean specifying whether the scope is currently visible.
     */
    Q_PROPERTY(bool isActive READ isActive WRITE setActive NOTIFY isActiveChanged)

    /**
     * @brief String specifying currently selected department
     */
    Q_PROPERTY(QString currentDepartmentId READ currentDepartmentId NOTIFY currentDepartmentIdChanged)

    /**
     * @brief Boolean specifying whether current query has departments.
     */
    Q_PROPERTY(bool hasDepartments READ hasDepartments NOTIFY hasDepartmentsChanged)

    /**
     * @brief VariantMap with customization properties
     */
    Q_PROPERTY(QVariantMap customizations READ customizations NOTIFY customizationsChanged)

protected:
    /// @cond
    explicit ScopeInterface(QObject* parent = 0) : QObject(parent) { }
    /// @endcond

public:

    // @cond
    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual QString iconHint() const = 0;
    virtual QString description() const = 0;
    virtual QString searchHint() const = 0;
    virtual bool visible() const = 0;
    virtual QString shortcut() const = 0;
    virtual bool searchInProgress() const = 0;
    virtual CategoriesInterface* categories() const = 0;
    virtual QString searchQuery() const = 0;
    virtual QString noResultsHint() const = 0;
    virtual QString formFactor() const = 0;
    virtual bool isActive() const = 0;
    virtual QString currentDepartmentId() const = 0;
    virtual bool hasDepartments() const = 0;
    virtual QVariantMap customizations() const = 0;

    /* setters */
    virtual void setSearchQuery(const QString& search_query) = 0;
    virtual void setNoResultsHint(const QString& hint) = 0;
    virtual void setFormFactor(const QString& form_factor) = 0;
    virtual void setActive(const bool) = 0;
    // @endcond

    /**
     * @brief Method used to activate a result.
     */
    Q_INVOKABLE virtual void activate(QVariant const& result) = 0;

    /**
     * @brief Method used to preview a result.
     *
     * Returns a new PreviewStackInterface instance. It's caller's responsibility
     * to free it.
     */
    Q_INVOKABLE virtual unity::shell::scopes::PreviewStackInterface* preview(QVariant const& result) = 0;

    /**
     * @brief Cancels the current activation.
     */
    Q_INVOKABLE virtual void cancelActivation() = 0;

    /**
     * @brief Closes the temporary scope which got opened when openScope was emitted.
     */
    Q_INVOKABLE virtual void closeScope(unity::shell::scopes::ScopeInterface* scope) = 0;

    /**
     * @brief Get a DepartmentInterface instance for the passed departmentId.
     */
    Q_INVOKABLE virtual unity::shell::scopes::DepartmentInterface* getDepartment(QString const& departmentId) = 0;

    /**
     * @brief Activate department by its id.
     *
     * This effectively runs a new query.
     */
    Q_INVOKABLE virtual void loadDepartment(QString const& departmentId) = 0;

Q_SIGNALS:
    // @cond
    void idChanged();
    void nameChanged();
    void iconHintChanged();
    void descriptionChanged();
    void searchHintChanged();
    void searchInProgressChanged();
    void visibleChanged();
    void shortcutChanged();
    void categoriesChanged();
    void searchQueryChanged();
    void noResultsHintChanged();
    void formFactorChanged();
    void isActiveChanged();
    void hasDepartmentsChanged();
    void currentDepartmentIdChanged();
    void customizationsChanged();
    // @endcond

    // signals triggered by activate(..) or preview(..) requests.
    /**
     * @brief Signal requesting to show the dash.
     *
     * This signal is usually emitted after activating a result.
     */
    void showDash();

    /**
     * @brief Signal requesting to hide the dash.
     *
     * This signal is usually emitted after activating a result.
     */
    void hideDash();

    /**
     * @brief Signal requesting to open a uri.
     *
     * This signal is usually emitted after activating a result.
     */
    void gotoUri(QString const& uri);

    /**
     * @brief Signal requesting to preview a result.
     *
     * This signal is usually emitted after activating a result.
     */
    void previewRequested(QVariant const& result);

    /**
     * @brief Signal requesting to change the currently focused scope.
     */
    void gotoScope(QString const& scopeId);

    /**
     * @brief Signal requesting to show a temporary scope.
     */
    void openScope(unity::shell::scopes::ScopeInterface* scope);

    /**
     * @brief Signal requesting activation of an application.
     */
    void activateApplication(QString const& desktop);
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::ScopeInterface*)

#endif
