/*
 * Copyright (C) 2011 Canonical, Ltd.
 *
 * Authors:
 *  Michael Zanetti <michael.zanetti@canonical.com>
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

#ifndef LAUNCHERITEM_H
#define LAUNCHERITEM_H

#include "unity/config.h"

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace launcher
{

class UNITY_API LauncherItemInterface: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString desktopFile READ desktopFile CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString icon READ icon CONSTANT)
    Q_PROPERTY(bool favorite READ favorite WRITE setFavorite NOTIFY favoriteChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(bool recent READ recent WRITE setRecent NOTIFY recentChanged)

public:
    LauncherItemInterface(QObject *parent = 0): QObject(parent) {}
    virtual ~LauncherItemInterface() {}

    virtual QString desktopFile() const = 0;

    virtual QString name() const = 0;
    virtual QString icon() const = 0;

    virtual bool favorite() const = 0;
    virtual void setFavorite(bool favorite) = 0;

    virtual bool running() const = 0;
    virtual void setRunning(bool running) = 0;

    virtual bool recent() const = 0;
    virtual void setRecent(bool recent) = 0;

Q_SIGNALS:
    void favoriteChanged(bool favorite);
    void runningChanged(bool running);
    void recentChanged(bool running);
};

}
}
}

#endif
