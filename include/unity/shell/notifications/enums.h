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
 *      Michał Sawicz <michal.sawicz@canonical.com>
 */


#ifndef ENUMS_H
#define ENUMS_H

#include <unity/config.h>

#include <QtCore/QObject>

namespace unity {
namespace shell {
namespace notifications {


class UNITY_API Urgency : public QObject
{
    Q_OBJECT

    Q_ENUMS(UrgencyEnum)

public:
    enum class UrgencyEnum {
        Invalid = 0,
        Low,
        Normal,
        Critical
    };
};


class UNITY_API Type : public QObject
{
    Q_OBJECT

    Q_ENUMS(TypeEnum)

public:
    enum class TypeEnum {
        Invalid = 0,
        Confirmation,
        Ephemeral,
        Interactive,
        SnapDecision,
        Placeholder
    };
};


class UNITY_API Hint : public QObject
{
    Q_OBJECT

    Q_FLAGS(HintEnum)

public:
    enum HintEnum {
        Invalid    = 1 << 0,
        ButtonTint = 1 << 1,
        IconOnly   = 1 << 2
    };

    Q_DECLARE_FLAGS(Hints, HintEnum)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Hint::Hints)

} // namespace notifications
} // namespace shell
} // namespace unity

#endif // ENUMS_H
