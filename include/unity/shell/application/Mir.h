/*
 * Copyright (C) 2015-2016 Canonical, Ltd.
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

#ifndef UNITY_SHELL_APPLICATION_MIR_H
#define UNITY_SHELL_APPLICATION_MIR_H

#include <QObject>

/**
    @brief Acting mostly as a namespace to hold enums and such for use in QML
 */
class Mir : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(State)
    Q_ENUMS(OrientationAngle)
    Q_ENUMS(ShellChrome)
    Q_ENUMS(FormFactor)

    /**
        @brief Name of the mouse cursor to be used. Follows the X Cursor naming convention.

        Eg.: "left_ptr" is a left-sided pointer arrow
     */
    Q_PROPERTY(QString cursorName READ cursorName WRITE setCursorName NOTIFY cursorNameChanged)

    /**
      * Current (global) keymap, to be applied on the keyboard device
      *
      * E.g.: "cz+qwerty" -> "cz" layout, "qwerty" variant
      */
    Q_PROPERTY(QString currentKeymap READ currentKeymap WRITE setCurrentKeymap NOTIFY currentKeymapChanged)

public:
    /**
        @brief Surface type
     */
    enum Type {
        UnknownType,
        NormalType,
        UtilityType,
        DialogType,
        GlossType,
        FreeStyleType,
        MenuType,
        InputMethodType,
        SatelliteType,
        TipType,
    };

    /**
        @brief Surface state
     */
    enum State {
        UnknownState,
        RestoredState,
        MinimizedState,
        MaximizedState,
        FullscreenState,
        MaximizedLeftState,
        MaximizedRightState,
        HorizMaximizedState,
        VertMaximizedState,
        MaximizedTopLeftState,
        MaximizedTopRightState,
        MaximizedBottomLeftState,
        MaximizedBottomRightState,
        HiddenState,
    };

    /**
        @brief Surface orientation angle
     */
    enum OrientationAngle {
        Angle0 = 0,
        Angle90 = 90,
        Angle180 = 180,
        Angle270 = 270
    };

    /**
        @brief Shell chrome
     */
    enum ShellChrome {
        NormalChrome,
        LowChrome,
    };

    /**
        @brief Form Factor
     */
    enum FormFactor {
        FormFactorUnknown,
        FormFactorPhone,
        FormFactorTablet,
        FormFactorMonitor,
        FormFactorTV,
        FormFactorProjector,
    };

    /// @cond
    virtual void setCursorName(const QString &cursorName) = 0;
    virtual QString cursorName() const = 0;

    virtual QString currentKeymap() const = 0;
    virtual void setCurrentKeymap(const QString &currentKeymap) = 0;
    /// @endcond

Q_SIGNALS:
    /// @cond
    void cursorNameChanged(const QString &cursorName);
    void currentKeymapChanged(const QString &currentKeymap);
    /// @endcond
};

Q_DECLARE_METATYPE(Mir::Type)
Q_DECLARE_METATYPE(Mir::State)
Q_DECLARE_METATYPE(Mir::OrientationAngle)
Q_DECLARE_METATYPE(Mir::ShellChrome)
Q_DECLARE_METATYPE(Mir::FormFactor)

#endif // UNITY_SHELL_APPLICATION_MIR_H
