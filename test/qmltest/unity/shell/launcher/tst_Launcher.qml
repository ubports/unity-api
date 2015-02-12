/*
 * Copyright 2013 Canonical Ltd.
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
 * Authors:
 *      Michael Zanetti <michael.zanetti@canonical.com>
 */

import QtQuick 2.0
import QtTest 1.0
import TestUtil 0.1
import Unity.Launcher 0.1

Item {

    SignalSpy {
        id: signalSpy
    }

    Verifier {
        id: checkModelVerifier

        property var model: LauncherModel

        function test_model_data() {
            return [
                { tag: "LauncherModel[object]", type: "object" },
                { tag: "LauncherModel[LauncherModelInterface]", type: "unity::shell::launcher::LauncherModelInterface" },
            ];
        }

        function test_model(data) {
            object = model;
            name = "LauncherModel"

            verifyData(data);
        }
    }

    Verifier {
        when: checkModelVerifier.completed

        Repeater {
            id: repeater
            model: LauncherModel
            delegate: Item {
                property var roles: model
            }
        }

        Repeater {
            id: quickListRepeater
            model: LauncherModel.get(0).quickList
            delegate: Item {
                property var roles: model
            }
        }

        function initTestCase() {
            if (repeater.count < 5) {
                print("This Test Suite requires at least 5 items in the model.")
                fail()
            }
        }

        /* make sure all the required roles are exposed on Model */
        function test_model_roles_data() {
            return [
                        { tag: "Model.roles[appId]", role: "appId", type: "string" },
                        { tag: "Model.roles[name]", role: "name", type: "string" },
                        { tag: "Model.roles[icon]", role: "icon", type: "string" },
                        { tag: "Model.roles[pinned]", role: "pinned", type: "boolean" },
                        { tag: "Model.roles[running]", role: "running", type: "boolean" },
                        { tag: "Model.roles[recent]", role: "recent", type: "boolean" },
                        { tag: "Model.roles[progress]", role: "progress", type: "number" },
                        { tag: "Model.roles[count]", role: "count", type: "number" },
                        { tag: "Model.roles[countVisible]", role: "countVisible", type: "boolean" },
                        { tag: "Model.roles[focused]", role: "focused", type: "boolean" },
                    ];
        }

        function test_model_roles(data) {
            name = "LauncherModel"
            try {
                object = repeater.itemAt(0).roles;
            } catch(err) {
                object = undefined;
            }

            verifyData(data);
        }

        function test_model_methods_data() {
            return [
                { tag: "Model.methods[get]", method: "get" },
                { tag: "Model.methods[move]", method: "move" },
                { tag: "Model.methods[pin]", method: "pin" },
                { tag: "Model.methods[requestRemove]", method: "requestRemove" },
                { tag: "Model.methods[quickListActionInvoked]", method: "quickListActionInvoked" },
                { tag: "Model.methods[setUser]", method: "setUser" },
            ];
        }

        function test_model_methods(data) {
            name = "LauncherModel"
            object = LauncherModel;
            verifyData(data);
        }

        function test_model_properties_data() {
            return [
                { tag: "Model.properties[applicationManager]", property: "applicationManager", type: "unity::shell::application::ApplicationManagerInterface" },
                { tag: "Model.properties[onlyPinned]", property: "onlyPinned", type: "boolean" },
            ];
        }

        function test_model_properties(data) {
            name = "LauncherModel";
            object = LauncherModel;
            verifyData(data);
        }

        function test_item_properties_data() {
            return [
                { tag: "Item.properties[appId]", constant: "appId", type: "string" },
                { tag: "Item.properties[name]", constant: "name", type: "string" },
                { tag: "Item.properties[icon]", constant: "icon", type: "string" },
                { tag: "Item.properties[pinned]", property: "pinned", type: "boolean" },
                { tag: "Item.properties[recent]", property: "recent", type: "boolean" },
                { tag: "Item.properties[running]", property: "running", type: "boolean" },
                { tag: "Item.properties[progress]", property: "progress", type: "number" },
                { tag: "Item.properties[count]", property: "count", type: "number" },
                { tag: "Item.properties[countVisible]", property: "countVisible", type: "boolean" },
                { tag: "Item.properties[focused]", property: "focused", type: "boolean" },
                { tag: "Item.properties[quickList]", constant: "quickList", type: "object" },
            ];
        }

        function test_item_properties(data) {
            name = "LauncherItem"
            try {
                object = LauncherModel.get(0)
            } catch(err) {
                object = undefined;
                print(err)
            }

            verifyData(data)
        }

        function test_quicklist_model_roles_data() {
            return [
                { tag: "Model.roles[label]", role: "label", type: "string" },
                { tag: "Model.roles[icon]", role: "icon", type: "string" },
                { tag: "Model.roles[clickable]", role: "clickable", type: "boolean" },
            ];
        }

        function test_quicklist_model_roles(data) {
            name = "QuickListModel"
            try {
                object = quickListRepeater.itemAt(0).roles;
            } catch(err) {
                object = undefined;
            }

            verifyData(data);
        }
    }
}
