/*
 * Copyright (C) 2011 Canonical, Ltd.
 *
 * Authors:
 *  Michal Hruby <michal.hruby@canonical.com>
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

namespace unity
{
namespace shell
{
namespace scopes
{

class CategoriesInterface;
class PreviewStackInterface;

class UNITY_API ScopeInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString iconHint READ iconHint NOTIFY iconHintChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(QString searchHint READ searchHint NOTIFY searchHintChanged)
    Q_PROPERTY(bool searchInProgress READ searchInProgress NOTIFY searchInProgressChanged)
    Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)
    Q_PROPERTY(QString shortcut READ shortcut NOTIFY shortcutChanged)
    Q_PROPERTY(unity::shell::scopes::CategoriesInterface* categories READ categories NOTIFY categoriesChanged)

    Q_PROPERTY(QString searchQuery READ searchQuery WRITE setSearchQuery NOTIFY searchQueryChanged)
    Q_PROPERTY(QString noResultsHint READ noResultsHint WRITE setNoResultsHint NOTIFY noResultsHintChanged)
    Q_PROPERTY(QString formFactor READ formFactor WRITE setFormFactor NOTIFY formFactorChanged)
    Q_PROPERTY(bool isActive READ isActive WRITE setActive NOTIFY isActiveChanged)

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

    /* setters */
    virtual void setSearchQuery(const QString& search_query) = 0;
    virtual void setNoResultsHint(const QString& hint) = 0;
    virtual void setFormFactor(const QString& form_factor) = 0;
    virtual void setActive(const bool) = 0;
    // @endcond

    Q_INVOKABLE virtual void activate(QVariant const& result) = 0;
    Q_INVOKABLE virtual unity::shell::scopes::PreviewStackInterface* preview(QVariant const& result) = 0;
    Q_INVOKABLE virtual void cancelActivation() = 0;
    Q_INVOKABLE virtual void closeScope(unity::shell::scopes::ScopeInterface* scope) = 0;

Q_SIGNALS:
    // @cond
    void idChanged();
    void nameChanged(const QString&);
    void iconHintChanged(const QString&);
    void descriptionChanged(const QString&);
    void searchHintChanged(const QString&);
    void searchInProgressChanged();
    void visibleChanged(bool);
    void shortcutChanged(const QString&);
    void categoriesChanged();
    void searchQueryChanged();
    void noResultsHintChanged();
    void formFactorChanged();
    void isActiveChanged(bool);
    // @endcond

    // signals triggered by activate(..) or preview(..) requests.
    void showDash();
    void hideDash();
    void gotoUri(QString const& uri);
    void activated();
    void previewRequested(QVariant const& result);
    void gotoScope(QString const& scopeId);
    void openScope(unity::shell::scopes::ScopeInterface* scope);

    void activateApplication(QString const& desktop);
};

}
}
}

Q_DECLARE_METATYPE(unity::shell::scopes::ScopeInterface*)

#endif
