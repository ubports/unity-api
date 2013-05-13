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
import Unity.Notifications 0.1
import Unity.Notifications.Mocks 0.1 as Mocks

Item {

    Mocks.MockSource {
        id: mockSource
    }

    Verifier {
        id: typeTestCase

        property var model: Model
        property var source: Source

        function cleanup() {
            clear();
            Source.model = null;
        }

        function test_types_data() {
            return [
                { name: "Urgency", tag: "Urgency.Invalid", enum: "Invalid" },
                { name: "Urgency", tag: "Urgency.Low", enum: "Low" },
                { name: "Urgency", tag: "Urgency.Normal", enum: "Normal" },
                { name: "Urgency", tag: "Urgency.Critical", enum: "Critical" },
                { name: "Type", tag: "Type.Invalid", enum: "Invalid" },
                { name: "Type", tag: "Type.Confirmation", enum: "Confirmation" },
                { name: "Type", tag: "Type.Ephemeral", enum: "Ephemeral" },
                { name: "Type", tag: "Type.Interactive", enum: "Ephemeral" },
                { name: "Type", tag: "Type.SnapDecision", enum: "SnapDecision" },
                { name: "Type", tag: "Type.Placeholder", enum: "Placeholder" },
                { name: "Hint", tag: "Hint.Invalid", enum: "Invalid" },
                { name: "Hint", tag: "Hint.ButtonTint", enum: "ButtonTint" },
                { name: "Hint", tag: "Hint.IconOnly", enum: "IconOnly" },
                { name: "Notification", tag: "Notification" },
            ];
        }

        function test_types(data) {
            try {
                object = eval(data.name);
            } catch(err) {
                object = undefined;
            }
            name = data.name;

            verifyData(data);
        }

        function test_model_data() {
            return [
                { tag: "Model[object]", type: "object" },
                { tag: "Model[ModelInterface]", type: "unity::shell::notifications::ModelInterface" },
                { tag: "Model.confirmationPlaceholder", writable: "confirmationPlaceholder",
                  type: "boolean", value: !Model.confirmationPlaceholder }
            ];
        }

        function test_model(data) {
            object = model;
            name = "Model"

            verifyData(data);
        }

        function test_source_data() {
            return [
                { tag: "Source[object]", type: "object" },
                { tag: "Source[SourceInterface]", type: "unity::shell::notifications::SourceInterface" },
                { tag: "Source.model", writable: "model", type: "object", value: model },
            ];
        }

        function test_source(data) {
            object = source;
            name = "Source"

            verifyData(data);
        }
    }

    Verifier {
       when: typeTestCase.completed
       optional: true

       Repeater {
           id: repeater
           delegate: Item {
               id: item
               property var roles: model
               property Repeater actionRepeater: actions

               Repeater {
                   id: actions
                   model: parent.roles.actions
                   delegate: Item {
                       property var roles: model
                   }
               }
           }
       }

       SignalSpy {
           id: dataSpy
           signalName: "dataChanged"
       }

       function initTestCase() {
           repeater.model = Model;
           dataSpy.target = Model;
           mockSource.model = Model;
       }

       function init() {
           tryCompare(repeater, "count", 0);
       }

       function cleanup() {
           Model.confirmationPlaceholder = false;
           // dismiss all Notifications
           for (var i = 0; i < repeater.count; i++) {
               repeater.itemAt(i).roles.notification.dismissed()
           }
           dataSpy.clear()
           tryCompare(repeater, "count", 0);
       }

       /* make sure all the required roles are exposed on Model */
       function test_model_roles_data() {
           return [
               { tag: "Model.roles[notification]", role: "notification", type: "object" },
               { tag: "Model.roles[type]", role: "type", type: "number" },
               { tag: "Model.roles[urgency]", role: "urgency", type: "number" },
               { tag: "Model.roles[id]", role: "id", type: "number" },
               { tag: "Model.roles[summary]", role: "summary", type: "string" },
               { tag: "Model.roles[body]", role: "body", type: "string" },
               { tag: "Model.roles[value]", role: "value", type: "number" },
               { tag: "Model.roles[icon]", role: "icon", type: "object" },
               { tag: "Model.roles[secondaryIcon]", role: "secondaryIcon", type: "object" },
               { tag: "Model.roles[actions]", role: "actions", type: "object" },
               { tag: "Model.roles[hints]", role: "hints", type: "number" },
           ];
       }

       function test_model_roles(data) {
           mockSource.send({});
           tryCompare(repeater, "count", 1);

           try {
               object = repeater.itemAt(0).roles;
           } catch(err) {
               object = undefined;
           }
           name = "Model";

           verifyData(data);
       }

       /* make sure all the members of Notification objects are available */
       function test_notification_members_data() {
            return [
                { tag: "Notification.dismissed", signal: "dismissed" },
                { tag: "Notification.onHovered", slot: "onHovered" },
                { tag: "Notification.onDisplayed", slot: "onDisplayed" },
                { tag: "Notification.invokeAction", method: "invokeAction" }
            ];
       }

       function test_notification_members(data) {
           mockSource.send({});
           tryCompare(repeater, "count", 1);

           try {
               object = repeater.itemAt(0).roles.notification;
           } catch(err) {
               object = undefined;
           }
           name = "Notification";

           verifyData(data);
       }

       /* make sure all the required roles for actions are exposed */
       function test_action_members_data() {
           return [
               { tag: "actions.roles[label]", role: "label", type: "string" },
               { tag: "actions.roles[id]", role: "id", type: "string" }
           ];
       }

       function test_action_members(data) {
           mockSource.send({
               "actions": [
                   {"label": "test", "id": "test"}
               ]
           });
           tryCompare(repeater, "count", 1);
           tryCompare(repeater.itemAt(0).actionRepeater, "count", 1);

           try {
               object = repeater.itemAt(0).actionRepeater.itemAt(0).roles;
           } catch(err) {
               object = undefined;
           }
           name = "actions";

           verifyData(data);
       }

       /* make sure the model is empty by default */
       function test_empty() {
           tryCompare(repeater, "count", 0);
       }

       /* make sure there is a placeholder item used as the first one when
          confirmationPlaceholder is true and that any additional notification is added
          after it */
       function test_placeholder() {
           Model.confirmationPlaceholder = true;
           tryCompare(repeater, "count", 1);

           compare(repeater.itemAt(0).roles.type, Type.Placeholder, "the notification should be of Placeholder type");
           mockSource.send({
               type: Type.Ephemeral
           })
           tryCompare(repeater, "count", 2);

           compare(repeater.itemAt(0).roles.type, Type.Placeholder, "the first notification should be of Placeholder type");
           compare(repeater.itemAt(1).roles.type, Type.Ephemeral, "the second notification should be of Ephemeral type");
       }

       /* make sure the placeholder item is updated with roles incoming in a Confirmation
          notification */
       function test_confirmation() {
           Model.confirmationPlaceholder = true;
           tryCompare(repeater, "count", 1);
           mockSource.send({
               "type": Type.Confirmation
           });
           tryCompare(repeater, "count", 1);
           dataSpy.wait();
           compare(repeater.count, 1, "there should be only one notification");
           compare(repeater.itemAt(0).roles.type, Type.Confirmation, "the first notification should be of Confirmation type");
       }
    }
}
