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


#ifndef UNITY_SHELL_NOTIFICATIONS_MODELINTERFACE_H
#define UNITY_SHELL_NOTIFICATIONS_MODELINTERFACE_H

#include <unity/config.h>

#include <QtCore/QAbstractListModel>

namespace unity
{

namespace shell
{

namespace notifications
{


class UNITY_API ModelInterface : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool confirmationPlaceholder READ confirmationPlaceholder WRITE setConfirmationPlaceholder NOTIFY confirmationPlaceholderChanged)

public:
    explicit ModelInterface(QObject* parent = 0) : QAbstractListModel(parent) { }
    virtual ~ModelInterface() { }

    virtual bool confirmationPlaceholder() const = 0;

    virtual void setConfirmationPlaceholder(bool confirmationPlaceholder) = 0;

Q_SIGNALS:
    void confirmationPlaceholderChanged(bool confirmationPlaceholder);
};

} // namespace notifications

} // namespace shell

} // namespace unity

#endif // UNITY_SHELL_NOTIFICATIONS_MODELINTERFACE_H
