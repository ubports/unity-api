/*
 * Copyright (C) 2012, 2013 Canonical, Ltd.
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
 */

import QtQuick 2.0
import QtTest 1.0
import TestUtil 0.1

TestCase {
    id: root

    /* object is the object on which the tests are carried out, name is used
       to identify the object in human-readable way */
    property var object
    property string name

    /* these are the default fail strings used during verification
       they can be overriden here or via optional arguments to the
       methods below */
    property string registeredMsg: strings.registeredMsg
    property string typeMsg: strings.typeMsg
    property string propTypeMsg: strings.propTypeMsg
    property string enumMsg: strings.enumMsg

    property string constantMsg: strings.constantMsg
    property string changedMsg: strings.changedMsg
    property string spyValidMsg: strings.spyValidMsg
    property string spyClearMsg: strings.spyClearMsg
    property string writableMsg: strings.writableMsg
    property string assignmentMsg: strings.assignmentMsg
    property string roleMsg: strings.roleMsg

    property string signalMsg: strings.signalMsg
    property string slotMsg: strings.slotMsg
    property string methodMsg: strings.methodMsg

    QtObject {
        id: strings

        readonly property string registeredMsg: "%1 should be a registered type"
        readonly property string typeMsg: "%1 should be of type %2"
        readonly property string propTypeMsg: "%1.%2 should be of type %3"
        readonly property string enumMsg: "there should be an %1::%2 enum"

        readonly property string constantMsg: "%1.%2 should be a property of type %3"
        readonly property string changedMsg: "%1 should have a %2Changed signal"
        readonly property string spyValidMsg: "connection to %1.%2Changed failed"
        readonly property string spyClearMsg: "%1.%2Changed signal emitted spuriously"
        readonly property string writableMsg: "%1.%2 should be writable"
        readonly property string assignmentMsg: "assignment to %1.%2 did not work"
        readonly property string roleMsg: "%1 should expose a \"%2\" role of type %3"

        readonly property string signalMsg: "there should be a %1.%2 signal"
        readonly property string slotMsg: "there should be a %1.%2 slot"
        readonly property string methodMsg: "there should be a %1.%2 method"
    }

    SignalSpy {
        id: spy
        target: root.object
    }

    /* verify that $value is of $type, otherwise fail with $msg */
    function verifyType(value, type, msg) {
        if (value === undefined) {
            fail(msg);
        }

        var baseTypes = ["number", "boolean", "string", "function", "object"];

        if (baseTypes.indexOf(type) >= 0) {
            compare(typeof value, type, msg);
        } else {
            compare(typeof value, "object", msg);
            verify(Util.isInstanceOf(value, type), msg);
        }
    }

    /* verify that $object has $member is of $type, otherwise fail with $msg */
    function verifyMember(object, member, type, msg) {
        if (object === undefined) {
            fail(msg);
        }

        if (type === "url") {
            if (!Util.objectHasPropertyOfType(object, member, "QUrl")) {
                fail(msg);
            }
        } else if (type === "color") {
            if (!Util.objectHasPropertyOfType(object, member, "QColor")) {
                fail(msg);
            }
        } else {
            verifyType(object[member], type, msg);
        }
    }

    /* verify that the object is registered */
    function registered(msg) {
        verifyType(object, "object", (msg || registeredMsg.arg(name)));
    }

    /* verify that the object is of $type */
    function type(type, msg) {
        verifyType(object, type, (msg || typeMsg.arg(name).arg(type)));
    }

    /* verify that there's a $member of $type */
    function  propType(member, type, msg) {
        verifyMember(object, member, type, (msg || propTypeMsg.arg(name).arg(member).arg(type)));
    }

    /* verify that there's an enum named $name */
    function enums(name, msg) {
        verifyMember(object, name, "number", (msg || enumMsg.arg(root.name).arg(name)));
    }

    /* verify that there's a $prop of $type */
    function constant(prop, type, msg) {
        verifyMember(object, prop, type, (msg || constantMsg.arg(name).arg(prop).arg(type)));
    }

    /* verify that there's a $prop of $type and a corresponding $typeChanged signal */
    function property(prop, type, msg1, msg2, msg3) {
        constant(prop, type);
        verifyMember(object, prop+"Changed", "function", (msg1 || changedMsg.arg(name).arg(prop)));
        spy.signalName = prop+"Changed";
        verify(spy.valid, (msg2 || spyValidMsg.arg(name).arg(prop)));
        compare(spy.count, 0, (msg3 || spyClearMsg.arg(name).arg(prop)));
    }

    /* verify that there's a writable $prop of $type */
    function writable(prop, type, value, msg1, msg2, msg3) {
        property(prop, type);
        var tmp = object[prop];
        try {
            object[prop] = value;
        } catch(err) {
            fail((msg1 || writableMsg.arg(name).arg(prop)));
        }
        compare(object[prop], value, (msg2 || assignmentMsg.arg(name).arg(prop)));
        spy.wait();
        object[prop] = tmp;
    }

    /* verify that there's a $role of $type exposed */
    function role(role, type, msg) {
        constant(role, type, msg || roleMsg.arg(name).arg(role).arg(type));
    }

    /* _data()-driven test helper */
    function verifyData(data) {
        if (data.enum !== undefined) {
            enums(data.enum);
        } else if (data.constant !== undefined) {
            constant(data.constant, data.type);
        } else if (data.property !== undefined) {
            property(data.property, data.type);
        } else if (data.writable !== undefined) {
            writable(data.writable, data.type, data.value);
        } else if (data.role !== undefined) {
            role(data.role, data.type);
        } else if (data.signal !== undefined) {
            propType(data.signal, "function", signalMsg.arg(name).arg(data.signal));
        } else if (data.slot !== undefined) {
            propType(data.slot, "function", slotMsg.arg(name).arg(data.slot));
        } else if (data.method !== undefined) {
            propType(data.method, "function", methodMsg.arg(name).arg(data.method));
        } else if (data.type !== undefined) {
            type(data.type);
        } else {
            registered();
        }
    }

    /* clear the properties */
    function clear() {
        object = undefined;
        name = "";
        spy.signalName = "";
        spy.clear();
    }
}
