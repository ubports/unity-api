/*
 * Copyright 2014 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <TestScopesPlugin.h>

#include <QtQml/qqml.h>

#include "CategoriesInterface.h"
#include "NavigationInterface.h"
#include "ResultsModelInterface.h"
#include "PreviewModelInterface.h"
#include "PreviewWidgetModelInterface.h"
#include "SettingsModelInterface.h"
#include "FiltersInterface.h"
#include "FilterBaseInterface.h"
#include "OptionSelectorOptionsInterface.h"
#include "OptionSelectorFilterInterface.h"
#include "Mocks/MockScopes.h"
#include "Mocks/MockScope.h"

void TestScopesPlugin::registerTypes(const char* uri)
{
    qmlRegisterType<MockScopes>(uri, 0, 2, "Scopes");
    qmlRegisterUncreatableType<unity::shell::scopes::ScopeInterface>(uri, 0, 2, "Scope", "Can't create Categories object in QML. Get them from Scopes instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::CategoriesInterface>(uri, 0, 2, "Categories", "Can't create Categories object in QML. Get them from Scope instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::NavigationInterface>(uri, 0, 2, "Navigation", "Can't create Navigation object in QML. Get them from Scope instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::ResultsModelInterface>(uri, 0, 2, "ResultsModel", "Can't create new ResultsModel in QML. Get them from Categories instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::PreviewModelInterface>(uri, 0, 2, "PreviewModel", "Can't create new PreviewModel in QML. Get them from Scope instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::PreviewWidgetModelInterface>(uri, 0, 2, "PreviewWidgetModel", "Can't create new PreviewWidgetModel in QML. Get them from PreviewModel instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::SettingsModelInterface>(uri, 0, 2, "Settings", "Can't create new Settings in QML. Get them from Scope instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::FilterBaseInterface>(uri, 0, 2, "FilterBase", "Can't create new Filter in QML. Get them from Filters instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::FiltersInterface>(uri, 0, 2, "Filters", "Can't create new Filters in QML. Get them from Scope instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::OptionSelectorOptionsInterface>(uri, 0, 2, "OptionSelectorOptions", "Can't create new OptionSelectorOptions in QML. Get them from OptionSelectorFilter instance.");
    qmlRegisterUncreatableType<unity::shell::scopes::OptionSelectorFilterInterface>(uri, 0, 2, "OptionSelectorFilter", "Can't create new OptionSelectorFilter in QML. Get them from Scope instance.");
}
