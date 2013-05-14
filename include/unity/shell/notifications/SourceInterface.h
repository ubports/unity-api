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


#ifndef UNITY_SHELL_NOTIFICATIONS_SOURCEINTERFACE_H
#define UNITY_SHELL_NOTIFICATIONS_SOURCEINTERFACE_H

#include <unity/config.h>

#include <QtCore/QObject>

namespace unity
{

namespace shell
{

namespace notifications
{


class ModelInterface;

class UNITY_API SourceInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(unity::shell::notifications::ModelInterface* model READ model WRITE setModel NOTIFY modelChanged)
public:
    explicit SourceInterface(QObject* parent = 0) : QObject(parent) { }
    virtual ~SourceInterface() { }

    virtual ModelInterface* model() const = 0;

    virtual void setModel(ModelInterface* model) = 0;

Q_SIGNALS:
    void modelChanged(ModelInterface* model);
};

} // namespace notifications

} // namespace shell

} // namespace unity

#endif // UNITY_SHELL_NOTIFICATIONS_SOURCEINTERFACE_H
