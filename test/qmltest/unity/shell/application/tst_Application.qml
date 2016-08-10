/*
 * Copyright 2013,2015 Canonical Ltd.
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
import Unity.Application 0.1

Item {

    SignalSpy {
        id: signalSpy
    }

    Verifier {
        id: checkModelVerifier

        property var model: ApplicationManager

        function test_model_data() {
            return [
                { tag: "ApplicationManager[object]", type: "object" },
                { tag: "ApplicationManager[ApplicationManagerInterface]", type: "unity::shell::application::ApplicationManagerInterface" },
            ];
        }

        function test_model(data) {
            object = model;
            name = "ApplicationManager"

            verifyData(data);
        }
    }

    Verifier {
        when: checkModelVerifier.completed

        Repeater {
            id: repeater
            model: ApplicationManager
            delegate: Item {
                property var roles: model
            }
        }

        /* make sure all the required roles are exposed on ApplicationManager */
        function test_model_roles_enum_data() {
            return [
                        { enum: "RoleAppId" },
                        { enum: "RoleName" },
                        { enum: "RoleComment" },
                        { enum: "RoleIcon" },
                        { enum: "RoleState" },
                        { enum: "RoleFocused" },
                        { enum: "RoleIsTouchApp" },
                        { enum: "RoleExemptFromLifecycle" },
                    ];
        }

        function test_model_roles_enum(data) {
            name = "ApplicationManager"
            object = ApplicationManager

            verifyData(data);
        }

        function test_model_roles_data() {
            return [
                        { tag: "ApplicationManager.roles[appId]", role: "appId", type: "string" },
                        { tag: "ApplicationManager.roles[name]", role: "name", type: "string" },
                        { tag: "ApplicationManager.roles[comment]", role: "comment", type: "string" },
                        { tag: "ApplicationManager.roles[icon]", role: "icon", type: "object" },
                        { tag: "ApplicationManager.roles[state]", role: "state", type: "number" },
                        { tag: "ApplicationManager.roles[focused]", role: "focused", type: "boolean" },
                        { tag: "ApplicationManager.roles[isTouchApp]", role: "isTouchApp", type: "boolean" },
                        { tag: "ApplicationManager.roles[exemptFromLifecycle]", role: "exemptFromLifecycle", type: "boolean" },
                    ];
        }

        function test_model_roles(data) {
            name = "ApplicationManager"
            try {
                object = repeater.itemAt(0).roles;
            } catch(err) {
                object = undefined;
            }

            verifyData(data);
        }

        function test_model_methods_data() {
            return [
                { tag: "ApplicationManager.methods[get]", method: "get" },
                { tag: "ApplicationManager.methods[findApplication]", method: "findApplication" },
                { tag: "ApplicationManager.methods[requestFocusApplication]", method: "requestFocusApplication" },
                { tag: "ApplicationManager.methods[focusApplication]", method: "focusApplication" },
                { tag: "ApplicationManager.methods[unfocusCurrentApplication]", method: "unfocusCurrentApplication" },
                { tag: "ApplicationManager.methods[startApplication]", method: "startApplication" },
                { tag: "ApplicationManager.methods[stopApplication]", method: "stopApplication" },
            ];
        }

        function test_model_methods(data) {
            name = "ApplicationManager";
            object = ApplicationManager;
            verifyData(data);
        }

        function test_model_properties_data() {
            return [
                { tag: "ApplicationManager.count", property: "count", type: "number" },
                { tag: "ApplicationManager.focusedApplicationId", property: "focusedApplicationId", type: "string" },
            ];
        }

        function test_model_properties(data) {
            name = "ApplicationManager";
            object = ApplicationManager;
            verifyData(data);
        }

        function test_item_properties_data() {
            return [
                { tag: "ApplicationInfo.properties[appId]", constant: "appId", type: "string" },
                { tag: "ApplicationInfo.properties[name]", property: "name", type: "string" },
                { tag: "ApplicationInfo.properties[comment]", property: "comment", type: "string" },
                { tag: "ApplicationInfo.properties[icon]", property: "icon", type: "object" },
                { tag: "ApplicationInfo.properties[state]", property: "state", type: "number" },
                { tag: "ApplicationInfo.properties[requestedState]", property: "requestedState", type: "number" },
                { tag: "ApplicationInfo.properties[focused]", property: "focused", type: "boolean" },
                { tag: "ApplicationInfo.properties[isTouchApp]", constant: "isTouchApp", type: "boolean" },
                { tag: "ApplicationInfo.properties[exemptFromLifecycle]", constant: "exemptFromLifecycle", type: "boolean" },
                { tag: "ApplicationInfo.properties[splashTitle]", constant: "splashTitle", type: "string" },
                { tag: "ApplicationInfo.properties[splashImage]", constant: "splashImage", type: "url" },
                { tag: "ApplicationInfo.properties[splashShowHeader]", constant: "splashShowHeader", type: "boolean"},
                { tag: "ApplicationInfo.properties[splashColor]", constant: "splashColor", type: "color"},
                { tag: "ApplicationInfo.properties[splashColorHeader]", constant: "splashColorHeader", type: "color"},
                { tag: "ApplicationInfo.properties[splashColorFooter]", constant: "splashColorFooter", type: "color"},
                { tag: "ApplicationInfo.properties[supportedOrientations]", constant: "supportedOrientations", type: "number"},
                { tag: "ApplicationInfo.properties[rotatesWindowContents]", constant: "rotatesWindowContents", type: "boolean"},
            ];
        }

        function test_item_properties(data) {
            name = "ApplicationInfo"
            try {
                object = ApplicationManager.get(0)
            } catch(err) {
                object = undefined;
                print(err)
            }

            verifyData(data)
        }
    }
}
