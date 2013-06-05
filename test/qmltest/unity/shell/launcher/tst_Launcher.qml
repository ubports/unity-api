/*
 * Copyright 2013 Canonical Ltd.
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

import QtQuick 2.0
import QtTest 1.0
import TestUtil 0.1
import Unity.Launcher 0.1

Item {
    Verifier {

        Repeater {
            id: repeater
            model: LauncherModel
            delegate: Item {
                property var roles: model
            }
        }

        function initTestCase() {
        }

        function init() {
        }

        function cleanup() {
        }

        /* make sure all the required roles are exposed on Model */
        function test_model_roles_data() {
            return [
                        { tag: "Model.roles[desktopFile]", role: "desktopFile", type: "string" },
                        { tag: "Model.roles[name]", role: "name", type: "string" },
                        { tag: "Model.roles[icon]", role: "icon", type: "string" },
                        { tag: "Model.roles[favorite]", role: "favorite", type: "boolean" },
                        { tag: "Model.roles[running]", role: "running", type: "boolean" },
                        { tag: "Model.roles[recent]", role: "recent", type: "boolean" },
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
                        { tag: "Model.methods[move]", method: "move" }
            ];
        }

        function test_model_methods(data) {
            name = "LauncherModel"
            object = LauncherModel;
            verifyData(data);
        }

        function test_item_properties_data() {
            return [
                        { tag: "Item.properties[desktopFile]", property: "desktopFile", type: "string" },
                        { tag: "Item.properties[name]", property: "name", type: "string" },
                        { tag: "Item.properties[icon]", property: "icon", type: "string" },
                        { tag: "Item.properties[favorite]", property: "favorite", type: "boolean" },
                        { tag: "Item.properties[recent]", property: "recent", type: "boolean" },
                        { tag: "Item.properties[running]", property: "running", type: "boolean" },
                    ];
        }

        function test_item_properties(data) {
            name = "LauncherItem"
            try {
                print("### 1", LauncherModel)
                print("### 2", LauncherModel["get"])
                print("### 5", LauncherModel.get(0))
                object = LauncherModel.get(0)
                print("### 3", object)
            } catch(err) {
                object = undefined;
                print("### 4", object)
            }
            print("######################", object)

            verifyData(data)
        }
    }
}
