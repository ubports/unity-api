/*
 * Copyright (C) 2015 Canonical, Ltd.
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
    @brief Acting as a namespace to hold enums and such for use in QML
 */
class Mir
{
    Q_GADGET
    Q_ENUMS(Type)
    Q_ENUMS(State)
    Q_ENUMS(OrientationAngle)

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
        VertMaximizedState,
        FullscreenState,
        HorizMaximizedState,
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
};

Q_DECLARE_METATYPE(Mir::OrientationAngle)

#endif // UNITY_SHELL_APPLICATION_MIR_H
