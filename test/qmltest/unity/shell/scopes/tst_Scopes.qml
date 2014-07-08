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

import QtQuick 2.0
import QtTest 1.0
import TestUtil 0.1
import Unity.Scopes 0.2

Item {
    id: root

    Scopes {
        id: scopes
    }
    property var scope: scopes.getScope(0)
    property var preview: root.scope.preview("")
    property var department: root.scope.getDepartment("root")

    Verifier {
        id: scopesVerifier

        Repeater {
             id: repeater
             model: scopes
             delegate: Item {
                 property var roles: model
             }
        }

        function test_scopes_data() {
            return [
                { tag: "Scopes[object]", type: "object" },
                { tag: "Scopes[ScopesInterface]", type: "unity::shell::scopes::ScopesInterface" },
            ];
        }

        function test_scopes(data) {
            object = repeater.model;
            name = "Scopes";
            verifyData(data);
        }

        function test_scopes_roles_data() {
            return [
                { tag: "Model.roles[scope]", role: "scope", type: "object" },
                { tag: "Model.roles[id]", role: "id", type: "string" },
                { tag: "Model.roles[visible]", role: "visible", type: "boolean" },
                { tag: "Model.roles[title]", role: "title", type: "string" },
            ];
        }

        function test_scopes_roles(data) {
            object = repeater.itemAt(0).roles;
            name = "Scopes";
            verifyData(data);
        }

        function test_scopes_properties_data() {
            return [
                { tag: "Item.properties[loaded]", constant: "loaded", type: "boolean" }
            ];
        }

        function test_scopes_properties(data) {
            object = repeater.model;
            name = "Scopes";
            verifyData(data);
        }

        function test_scopes_methods_data() {
            return [
                { tag: "Model.methods[get]", method: "getScope" }
            ];
        }

        function test_scopes_methods(data) {
            object = repeater.model;
            name = "Scopes"
            verifyData(data);
        }
    }

    Verifier {
        id: scopeVerifier

        function test_scope_data() {
            return [
                { tag: "Scope[object]", type: "object" },
                { tag: "Scope[ScopeInterface]", type: "unity::shell::scopes::ScopeInterface" },
            ];
        }

        function test_scope(data) {
            object = root.scope;
            name = "Scope";
            verifyData(data);
        }

        function test_scope_properties_data() {
            return [
                { tag: "Item.properties[id]", constant: "id", type: "string" },
                { tag: "Item.properties[name]", constant: "name", type: "string" },
                { tag: "Item.properties[iconHint]", constant: "iconHint", type: "string" },
                { tag: "Item.properties[description]", constant: "description", type: "string" },
                { tag: "Item.properties[searchHint]", constant: "searchHint", type: "string" },
                { tag: "Item.properties[searchInProgress]", constant: "searchInProgress", type: "boolean" },
                { tag: "Item.properties[visible]", constant: "visible", type: "boolean" },
                { tag: "Item.properties[shortcut]", constant: "shortcut", type: "string" },
                { tag: "Item.properties[categories]", constant: "categories", type: "object" },
                { tag: "Item.properties[searchQuery]", constant: "searchQuery", type: "string" },
                { tag: "Item.properties[noResultsHint]", constant: "noResultsHint", type: "string" },
                { tag: "Item.properties[formFactor]", constant: "formFactor", type: "string" },
                { tag: "Item.properties[isActive]", constant: "isActive", type: "boolean" },
                { tag: "Item.properties[currentDepartmentId]", constant: "currentDepartmentId", type: "string" },
                { tag: "Item.properties[hasDepartments]", constant: "hasDepartments", type: "boolean" },
                { tag: "Item.properties[customizations]", constant: "customizations", type: "object" }
            ];
        }

        function test_scope_properties(data) {
            object = root.scope;
            name = "Scope";
            verifyData(data);
        }

        function test_scope_methods_data() {
            return [
                { tag: "Model.methods[activate]", method: "activate" },
                { tag: "Model.methods[preview]", method: "preview" },
                { tag: "Model.methods[cancelActivation]", method: "cancelActivation" },
                { tag: "Model.methods[closeScope]", method: "closeScope" },
                { tag: "Model.methods[showDash]", method: "showDash" },
                { tag: "Model.methods[hideDash]", method: "hideDash" },
                { tag: "Model.methods[gotoUri]", method: "gotoUri" },
                { tag: "Model.methods[previewRequested]", method: "previewRequested" },
                { tag: "Model.methods[gotoScope]", method: "gotoScope" },
                { tag: "Model.methods[openScope]", method: "openScope" },
                { tag: "Model.methods[activateApplication]", method: "activateApplication" },
                { tag: "Model.methods[getDepartment]", method: "getDepartment" },
                { tag: "Model.methods[loadDepartment]", method: "loadDepartment" }
            ];
        }

        function test_scope_methods(data) {
            object = root.scope;
            name = "Scope"
            verifyData(data);
        }
    }

    Verifier {
        id: categoriesVerifier

        Repeater {
             id: categoriesRepeater
             model: root.scope.categories
             delegate: Item {
                 property var roles: model
                 property var results: model.results
             }
        }

        function test_categories_data() {
            return [
                { tag: "Categories[object]", type: "object" },
                { tag: "Categories[CategoriesInterface]", type: "unity::shell::scopes::CategoriesInterface" },
            ];
        }

        function test_categories(data) {
            object = categoriesRepeater.model;
            name = "Categories";
            verifyData(data);
        }

        function test_categories_roles_data() {
            return [
                { tag: "Model.roles[categoryId]", role: "categoryId", type: "string" },
                { tag: "Model.roles[name]", role: "name", type: "string" },
                { tag: "Model.roles[icon]", role: "icon", type: "string" },
                { tag: "Model.roles[rawRendererTemplate]", role: "rawRendererTemplate", type: "string" },
                { tag: "Model.roles[renderer]", role: "renderer", type: "object" },
                { tag: "Model.roles[components]", role: "components", type: "object" },
                { tag: "Model.roles[results]", role: "results", type: "object" },
                { tag: "Model.roles[count]", role: "count", type: "number" },
            ];
        }

        function test_categories_roles(data) {
            object = categoriesRepeater.itemAt(0).roles;
            name = "Categories";
            verifyData(data);
        }

        function test_categories_methods_data() {
            return [
                { tag: "Model.methods[overrideCategoryJson]", method: "overrideCategoryJson" },
                { tag: "Model.methods[addSpecialCategory]", method: "addSpecialCategory" }
            ];
        }

        function test_categories_methods(data) {
            object = categoriesRepeater.model;
            name = "Categories"
            verifyData(data);
        }
    }

    Verifier {
        id: settingsVerifier

        Repeater {
             id: settingsRepeater
             model: root.scope.settings
             delegate: Item {
                 property var roles: model
             }
        }

        function test_settings_data() {
            return [
                { tag: "Settings[object]", type: "object" },
                { tag: "Settings[SettingsModelInterface]", type: "unity::shell::scopes::SettingsModelInterface" },
            ];
        }

        function test_settings(data) {
            object = settingsRepeater.model;
            name = "Settings";
            verifyData(data);
        }

        function test_settings_roles_data() {
            return [
                { tag: "Model.roles[settingId]", role: "settingId", type: "string" },
                { tag: "Model.roles[displayName]", role: "displayName", type: "string" },
                { tag: "Model.roles[type]", role: "type", type: "string" },
                { tag: "Model.roles[properties]", role: "properties", type: "object" },
                // the first mocked setting is of type boolean
                { tag: "Model.roles[value]", role: "value", type: "boolean" },
            ];
        }

        function test_settings_roles(data) {
            object = settingsRepeater.itemAt(0).roles;
            name = "Settings";
            verifyData(data);
        }

        function test_settings_properties_data() {
            return [
                { tag: "Item.properties[count]", constant: "count", type: "number" }
            ];
        }

        function test_settings_properties(data) {
            object = settingsRepeater.model;
            name = "Settings";
            verifyData(data);
        }
    }

    Verifier {
        id: resultsModelVerifier

        Repeater {
             id: resultsModelRepeater
             model: categoriesRepeater.count > 0 ? categoriesRepeater.itemAt(0).results : undefined
             delegate: Item {
                 property var roles: model
             }
        }

        function test_resultsModel_data() {
            return [
                { tag: "ResultsModel[object]", type: "object" },
                { tag: "ResultsModel[ResultsModelInterface]", type: "unity::shell::scopes::ResultsModelInterface" },
            ];
        }

        function test_resultsModel(data) {
            object = categoriesRepeater.itemAt(0).results;
            name = "ResultsModel";
            verifyData(data);
        }

        function test_resultsModel_roles_data() {
            return [
                { tag: "Model.roles[uri]", role: "uri", type: "string" },
                { tag: "Model.roles[categoryId]", role: "categoryId", type: "string" },
                { tag: "Model.roles[dndUri]", role: "dndUri", type: "string" },
                { tag: "Model.roles[result]", role: "result", type: "object" },
                { tag: "Model.roles[title]", role: "title", type: "string" },
                { tag: "Model.roles[art]", role: "art", type: "string" },
                { tag: "Model.roles[subtitle]", role: "subtitle", type: "string" },
                { tag: "Model.roles[mascot]", role: "mascot", type: "string" },
                { tag: "Model.roles[emblem]", role: "emblem", type: "string" },
                { tag: "Model.roles[summary]", role: "summary", type: "string" },
                { tag: "Model.roles[attributes]", role: "attributes", type: "string" },
                { tag: "Model.roles[background]", role: "background", type: "string" },
            ];
        }

        function test_resultsModel_roles(data) {
            object = resultsModelRepeater.itemAt(0).roles;
            name = "ResultsModel";
            verifyData(data);
        }

        function test_resultsModel_properties_data() {
            return [
                { tag: "Item.properties[categoryId]", constant: "categoryId", type: "string" },
                { tag: "Item.properties[count]", constant: "count", type: "number" }
            ];
        }

        function test_resultsModel_properties(data) {
            object = resultsModelRepeater.model;
            name = "ResultsModel";
            verifyData(data);
        }
    }

    Verifier {
        id: previewStackVerifier

        Repeater {
             id: previewStackRepeater
             model: preview
             delegate: Item {
                 property var roles: model
             }
        }

        function test_previewStack_data() {
            return [
                { tag: "PreviewStack[object]", type: "object" },
                { tag: "PreviewStack[PreviewStackInterface]", type: "unity::shell::scopes::PreviewStackInterface" },
            ];
        }

        function test_previewStack(data) {
            object = previewStackRepeater.model;
            name = "PreviewStack";
            verifyData(data);
        }

        function test_previewStack_roles_data() {
            return [
                { tag: "Model.roles[previewModel]", role: "previewModel", type: "object" }
            ];
        }

        function test_previewStack_roles(data) {
            object = previewStackRepeater.itemAt(0).roles;
            name = "PreviewStack";
            verifyData(data);
        }

        function test_previewStack_properties_data() {
            return [
                { tag: "Item.properties[widgetColumnCount]", constant: "widgetColumnCount", type: "number" }
            ];
        }

        function test_previewStack_properties(data) {
            object = previewStackRepeater.model;
            name = "PreviewStack";
            verifyData(data);
        }

        function test_previewStack_methods_data() {
            return [
                { tag: "Model.methods[get]", method: "getPreviewModel" }
            ];
        }

        function test_previewStack_methods(data) {
            object = previewStackRepeater.model;
            name = "PreviewStack"
            verifyData(data);
        }
    }

    Verifier {
        id: previewModelVerifier

        Repeater {
             id: previewModelRepeater
             model: preview.getPreviewModel(0)
             delegate: Item {
                 property var roles: model
                 property var columnModel: model.columnModel
             }
        }

        function test_previewModel_data() {
            return [
                { tag: "PreviewModel[object]", type: "object" },
                { tag: "PreviewModel[PreviewModelInterface]", type: "unity::shell::scopes::PreviewModelInterface" },
            ];
        }

        function test_previewModel(data) {
            object = previewModelRepeater.model;
            name = "PreviewModel";
            verifyData(data);
        }

        function test_previewModel_roles_data() {
            return [
                { tag: "Model.roles[columnModel]", role: "columnModel", type: "object" }
            ];
        }

        function test_previewModel_roles(data) {
            object = previewModelRepeater.itemAt(0).roles;
            name = "PreviewModel";
            verifyData(data);
        }

        function test_previewModel_properties_data() {
            return [
                { tag: "Item.properties[widgetColumnCount]", constant: "widgetColumnCount", type: "number" },
                { tag: "Item.properties[loaded]", constant: "loaded", type: "boolean" },
                { tag: "Item.properties[processingAction]", constant: "processingAction", type: "boolean" }
            ];
        }

        function test_previewModel_properties(data) {
            object = previewModelRepeater.model;
            name = "PreviewModel";
            verifyData(data);
        }

        function test_previewModel_methods_data() {
            return [
                { tag: "Model.methods[triggered]", method: "triggered" }
            ];
        }

        function test_previewModel_methods(data) {
            object = previewModelRepeater.model;
            name = "PreviewModel"
            verifyData(data);
        }
    }

    Verifier {
        id: previewWidgetModelVerifier

        Repeater {
             id: previewWidgetModelRepeater
             model: previewModelRepeater.count > 0 ? previewModelRepeater.itemAt(0).columnModel : undefined
             delegate: Item {
                 property var roles: model
             }
        }

        function test_previewWidgetModel_data() {
            return [
                { tag: "PreviewWidgetModel[object]", type: "object" },
                { tag: "PreviewWidgetModel[ScopesInterface]", type: "unity::shell::scopes::PreviewWidgetModelInterface" },
            ];
        }

        function test_previewWidgetModel(data) {
            object = previewWidgetModelRepeater.model;
            name = "PreviewWidgetModel";
            verifyData(data);
        }

        function test_previewWidgetModel_roles_data() {
            return [
                { tag: "Model.roles[widgetId]", role: "widgetId", type: "string" },
                { tag: "Model.roles[type]", role: "type", type: "string" },
                { tag: "Model.roles[properties]", role: "properties", type: "object" }
            ];
        }

        function test_previewWidgetModel_roles(data) {
            object = previewWidgetModelRepeater.itemAt(0).roles;
            name = "PreviewWidgetModel";
            verifyData(data);
        }
    }


    Verifier {
        id: departmentVerifier

        Repeater {
             id: departmentRepeater
             model: root.department
             delegate: Item {
                 property var roles: model
             }
        }

        function test_department_data() {
            return [
                { tag: "Department[object]", type: "object" },
                { tag: "Department[DepartmentInterface]", type: "unity::shell::scopes::DepartmentInterface" },
            ];
        }

        function test_department(data) {
            object = departmentRepeater.model;
            name = "Department";
            verifyData(data);
        }

        function test_department_roles_data() {
            return [
                { tag: "Model.roles[departmentId]", role: "departmentId", type: "string" },
                { tag: "Model.roles[label]", role: "label", type: "string" },
                { tag: "Model.roles[hasChildren]", role: "hasChildren", type: "boolean" },
                { tag: "Model.roles[isActive]", role: "isActive", type: "boolean" }
            ];
        }

        function test_department_roles(data) {
            object = departmentRepeater.itemAt(0).roles;
            name = "Department";
            verifyData(data);
        }

        function test_department_properties_data() {
            return [
                { tag: "Model.properties[departmentId]", constant: "departmentId", type: "string" },
                { tag: "Model.properties[label]", constant: "label", type: "string" },
                { tag: "Model.properties[allLabel]", constant: "allLabel", type: "string" },
                { tag: "Model.properties[parentDepartmentId]", constant: "parentDepartmentId", type: "string" },
                { tag: "Model.properties[parentLabel]", constant: "parentLabel", type: "string" },
                { tag: "Model.properties[loaded]", constant: "loaded", type: "boolean" },
                { tag: "Model.properties[isRoot]", constant: "isRoot", type: "boolean" },
                { tag: "Model.properties[count]", constant: "count", type: "number" }
            ];
        }

        function test_department_properties(data) {
            object = departmentRepeater.model;
            name = "Department";
            verifyData(data);
        }
    }
}
