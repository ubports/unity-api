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

#ifndef MOCKAPPLICATIONMANAGER_H
#define MOCKAPPLICATIONMANAGER_H

#include <ApplicationManagerInterface.h>

using namespace unity::shell::application;

class MockApplicationInfo;

class UNITY_API MockApplicationManager: public ApplicationManagerInterface
{
   Q_OBJECT

public:
    MockApplicationManager(QObject* parent = 0);
    ~MockApplicationManager();

    int rowCount(const QModelIndex& parent) const;

    QVariant data(const QModelIndex& index, int role) const;

    QString focusedApplicationId() const;

    Q_INVOKABLE unity::shell::application::ApplicationInfoInterface *get(const int index) const;

    Q_INVOKABLE unity::shell::application::ApplicationInfoInterface *findApplication(const QString &appId) const;

    ApplicationInfoInterface *findApplicationWithSurface(MirSurfaceInterface*) override { return nullptr; }

    Q_INVOKABLE bool requestFocusApplication(const QString &appId);

    Q_INVOKABLE bool focusApplication(const QString &appId);

    Q_INVOKABLE void unfocusCurrentApplication();

    Q_INVOKABLE unity::shell::application::ApplicationInfoInterface *startApplication(const QString &appId, const QStringList &arguments);

    Q_INVOKABLE bool stopApplication(const QString &appId);

private:
    QList<MockApplicationInfo*> m_list;
};

#endif // MOCKAPPLICATIONMANAGER_H
