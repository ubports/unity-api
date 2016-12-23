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


#ifndef UNITY_SHELL_NOTIFICATIONS_ENUMS_H
#define UNITY_SHELL_NOTIFICATIONS_ENUMS_H

#include <unity/SymbolExport.h>

#include <QtCore/QObject>

namespace unity
{

namespace shell
{

namespace notifications
{

/**
\brief Wraps NotificationInterface's urgency enumeration.
*/

class UNITY_API Urgency : public QObject
{
    Q_OBJECT

public:
    /**
    \brief NotificationInterface's urgency enumeration.

    This determines the order in which notifications are displayed.
    */
    enum class UrgencyEnum
    {
        Invalid = 0,
        Low,            /**< Displayed last. */
        Normal,         /**< Displayed before Low, after Critical. */
        Critical        /**< Displayed before Low and Normal. */
    };
    Q_ENUM(UrgencyEnum)
};


/**
\brief Wraps NotificationInterface's type enumeration.
*/

class UNITY_API Type : public QObject
{
    Q_OBJECT

public:
    /**
    \brief NotificationInterface's type enumeration.

    This determines the visual and interaction behavior of the displayed notification.
    */
    enum class TypeEnum
    {
        Invalid = 0,
        Confirmation,   /**< Confirmation (synchronous). */
        Ephemeral,      /**< Ephemeral (input-transparent). */
        Interactive,    /**< Interactive (clickable). */
        SnapDecision,   /**< Snap decision (multi-button). */
        Placeholder     /**< Non-visible placeholder of default size. */
    };
    Q_ENUM(TypeEnum)
};


/**
\brief Wraps NotificationInterface's hint flags.
*/

class UNITY_API Hint : public QObject
{
    Q_OBJECT

public:
    /**
    \brief NotificationInterface's hint flags.

    This modifies some visual and interactive behavior of the displayed notification.
    */
    enum HintEnum
    {
        Invalid    = 1 << 0,
        ButtonTint = 1 << 1,    /**< Use a colour tint on the positive button in a snap decision. */
        IconOnly   = 1 << 2     /**< Only display the icon, no summary or body. */
    };
    Q_FLAG(HintEnum)

    Q_DECLARE_FLAGS(Hints, HintEnum)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Hint::Hints)

} // namespace notifications

} // namespace shell

} // namespace unity

#endif // UNITY_SHELL_NOTIFICATIONS_ENUMS_H
