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

#ifndef UNITY_SHELL_APPLICATION_MIRFOCUSCONTROLLERINTERFACE_H
#define UNITY_SHELL_APPLICATION_MIRFOCUSCONTROLLERINTERFACE_H

#include <QObject>

namespace unity {
namespace shell {
namespace application {

class MirSurfaceInterface;

/**
 * @brief Defines which MirSurface has focus
 *
 * Even though QQuickWindow::activeFocusItem is who ultimately defines the focused MirSurface
 * in the QML scene, the two might not necessarily match all the time. And also this is a cleaner
 * way of keeping tabs on the focused MirSurface as it doesn't involve unrelated QML items.
 */
class MirFocusControllerInterface : public QObject
{
    Q_OBJECT

    /**
     * @brief The MirSurface which currently has focus, if any.
     *
     * Shell provides this information.
     *
     * But it can also be changed by the implementation. When a MirSurfaceItem gets active
     * focus from the QML scene, it will also call MirFocusController::setFocusedSurface for
     * the MirSurface it holds.
     */
    Q_PROPERTY(unity::shell::application::MirSurfaceInterface* focusedSurface READ focusedSurface
                                                                              WRITE setFocusedSurface
                                                                              NOTIFY focusedSurfaceChanged)
public:
    /// @cond
    MirFocusControllerInterface(QObject *parent = 0) : QObject(parent) {}
    virtual ~MirFocusControllerInterface() {}

    virtual void setFocusedSurface(MirSurfaceInterface *surface) = 0;
    virtual MirSurfaceInterface* focusedSurface() const = 0;
    /// @endcond
Q_SIGNALS:
    /// @cond
    void focusedSurfaceChanged();
    /// @endcond
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_MIRFOCUSCONTROLLERINTERFACE_H
