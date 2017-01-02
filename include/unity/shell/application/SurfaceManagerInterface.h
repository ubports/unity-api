/*
 * Copyright (C) 2016 Canonical, Ltd.
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

#ifndef UNITY_SHELL_APPLICATION_SURFACEMANAGERINTERFACE_H
#define UNITY_SHELL_APPLICATION_SURFACEMANAGERINTERFACE_H

#include <QObject>
#include <QVector>

namespace unity {
namespace shell {
namespace application {

class MirSurfaceInterface;

class SurfaceManagerInterface : public QObject
{
    Q_OBJECT

public:
    virtual ~SurfaceManagerInterface() {}

    virtual void raise(MirSurfaceInterface *surface) = 0;
    virtual void activate(MirSurfaceInterface *surface) = 0;

Q_SIGNALS:
    void surfaceCreated(MirSurfaceInterface *surface);
    void surfacesRaised(const QVector<MirSurfaceInterface*> &surfaces);
    void modificationsStarted();
    void modificationsEnded();
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_SURFACEMANAGERINTERFACE_H
